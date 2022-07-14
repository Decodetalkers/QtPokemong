#include "game.h"
#include <QAbstractItemModel>
#include <QDebug>
#include <QFutureWatcher>
#include <QGSettings/QGSettings>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QRandomGenerator>
#include <QScopedPointer>
#include <QStringListModel>
#include <QtConcurrent>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QLabel;
class QListView;
class QHBoxLayout;
class QPushButton;
class QTableWidget;
class QTableView;
QT_END_NAMESPACE

// The baseurl from row github
const QString baseurl = "https://raw.githubusercontent.com/PokeAPI/sprites/"
                        "master/sprites/pokemon/%1.png";

// logined image
const QString loadinged = ":/resources/yousaki.jpg";

Switch::Switch(QWidget *parent, QLayout *mainlayout)
    : QWidget(parent)
{
    setLayout(mainlayout);
}

// dowmload the picture
QFuture<QByteArray> downloads(const QUrl url)
{
    return QtConcurrent::run([=] {
        QNetworkAccessManager qam = QNetworkAccessManager();
        QNetworkRequest request(url);
        auto before = qam.get(request);
        // await , oh ,sorry , cpp does have await now ,:(;
        {
            QEventLoop loop;
            QObject::connect(before, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            loop.exec();
        }
        auto newbefore = QScopedPointer(before);
        auto res = newbefore->readAll();
        if (before->error() != QNetworkReply::NoError) {
            qDebug() << "error";
        }
        QThread::sleep(3);
        return res;
    });
}
void Player::beenAttack(int attack)
{
    yourturn = true;
    hps = attack >= hps ? 0 : hps - attack;
    hpline->lifeUpdate(hps);
    hplabel->setText(QString("hp = %1").arg(hps));
    update();
    // dead
    emit sendmessage(QString("Player is damaged and lost %1 life!").arg(attack));
    if (hps == 0) {
        emit sendmessage(QString("Player is dead!"));
        QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher, this] {
            watcher->deleteLater();
            yourturn = false;
            emit beendefeated();
        });
        watcher->setFuture(QtConcurrent::run([=] { QThread::sleep(2); }));
    }
}
void Player::refrash()
{
    hps = 100;
    hpline->lifeUpdate(hps);
    hplabel->setText(QString("hp = %1").arg(hps));
    yourturn = true;
    update();
}
Player::Player(QWidget *parent, QSharedPointer<PokeMonModel> model)
    : QWidget(parent)
    , pokemonmodel(model)
{
    QHBoxLayout *panel = new QHBoxLayout();

    QGridLayout *buttons = new QGridLayout();

    QPushButton *aa = new QPushButton("A", this);

    buttons->addWidget(aa, 0, 0, 1, 1);
    aa->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPushButton *bb = new QPushButton("B", this);
    bb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttons->addWidget(bb, 0, 1, 1, 1);

    QPushButton *cc = new QPushButton("C", this);
    cc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttons->addWidget(cc, 1, 0, 1, 1);

    QPushButton *dd = new QPushButton("D", this);
    dd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttons->addWidget(dd, 1, 1, 1, 1);

    Switch *theswitch = new Switch(this, buttons);

    QTabWidget *selections = new QTabWidget(this);
    selections->addTab(theswitch, "first");

    QTableView *table = new QTableView();
    table->setItemDelegate(new PokemonTableDelegate);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setDefaultSectionSize(100);
    table->verticalHeader()->setDefaultSectionSize(100);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);
    QList<PokemongIcon> icons;
    icons << PokemongIcon();
    QList<QString> names;
    names << "shadoxi";
    // pokemonmodel = new PokeMonModel(this);
    pokemonmodel->populateData(icons, names);

    table->setModel(pokemonmodel.data());
    table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    table->horizontalHeader()->setStretchLastSection(true);
    // table->verticalHeader()->setStretchLastSection(true);
    selections->addTab(table, "Forth");

    // experiment end
    panel->addWidget(selections);
    QVBoxLayout *hp = new QVBoxLayout();
    {
        hpline = new Linerbar();
        hplabel = new QLabel(QString("hp = %1").arg(hps));
        hplabel->setAlignment(Qt::AlignRight);
        hp->addWidget(hpline);
        hp->addWidget(hplabel);
    }
    panel->addLayout(hp);
    QImage image = QImage(loadinged);
    player = new QLabel(this);
    player->setPixmap(QPixmap::fromImage(image));
    player->setScaledContents(true);
    player->setFixedWidth(200);
    player->setFixedHeight(200);
    panel->addWidget(player);

    setLayout(panel);

    connect(aa, &QPushButton::clicked, this, [&] {
        auto a = QRandomGenerator::global()->bounded(100);
        download(QUrl(QString(baseurl).arg(a)));
    });
    connect(bb, &QPushButton::clicked, this, [&] {
        if (yourturn) {
            emit sendmessage(QString("Player attack the enermy !"));
            emit attack(10);
            yourturn = false;
        }
    });

    connect(dd, &QPushButton::clicked, this, [&] {
        if (yourturn) {
            yourturn = false;
            emit sendmessage(QString("Player try to catch pokemong"));
            emit trycatch();
        }
    });
    // auto a = QRandomGenerator::global()->bounded(100);
    // download(QUrl(QString(baseurl).arg(a)));
}

// download new pixmap from www
void Player::download(const QUrl url)
{
    QFutureWatcher<QByteArray> *watcher = new QFutureWatcher<QByteArray>(this);
    QFuture<QByteArray> t1 = downloads(url);
    QImage image = QImage(loadinged);
    // player = new QLabel();
    player->setPixmap(QPixmap::fromImage(image));
    // panel->addWidget(player);
    connect(watcher, &QFutureWatcher<QByteArray>::finished, this, [watcher, this] {
        watcher->deleteLater();
        auto array = watcher->result();
        QPixmap image;
        image.loadFromData(array);
        player->setPixmap(image);
    });
    watcher->setFuture(t1);
}

// update the data, and show one more line
void Player::updatePokemonodel(PokemongIcon pokemon, QString name)
{
    pokemonmodel->updateData(pokemon, name);
}
Enermy::Enermy(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *panel = new QHBoxLayout();
    QVBoxLayout *hp = new QVBoxLayout();
    {
        hpline = new Linerbar();
        hplabel = new QLabel(QString("hp = %1").arg(hps));
        hp->addWidget(hpline);
        hp->addWidget(hplabel);
    }

    // QPushButton *button1 = new QPushButton("Shaoxi");
    enermy = new QLabel(this);
    enermy->setFixedWidth(200);
    enermy->setFixedHeight(200);
    enermy->setScaledContents(true);
    enermy->setPixmap(QPixmap::fromImage(QImage(loadinged)));
    panel->addWidget(enermy);
    panel->addLayout(hp);
    setLayout(panel);
    loading();
}

// loading the new pokemong
void Enermy::loading()
{
    auto a = QRandomGenerator::global()->bounded(100);
    pokemonid = a;
    QFutureWatcher<QByteArray> *watcher = new QFutureWatcher<QByteArray>(this);
    QFuture<QByteArray> get = downloads(QUrl(QString(baseurl).arg(a)));
    connect(watcher, &QFutureWatcher<QByteArray>::finished, this, [watcher, this] {
        watcher->deleteLater();
        auto array = watcher->result();
        QPixmap image;
        image.loadFromData(array);
        enermy->setPixmap(image);
    });
    watcher->setFuture(get);
}

// re enter
void Enermy::refresh()
{
    hps = 100;
    hpline->lifeUpdate(hps);
    hplabel->setText(QString("hp = %1").arg(hps));
    update();
    loading();
}

// try to catch it
void Enermy::trybecatched()
{
    auto a = QRandomGenerator::global()->bounded(100);
    if (a % 3 == 0) {
        emit sendmessage(QString("Pokemon is catched!"));

        QFutureWatcher<QByteArray> *watcher = new QFutureWatcher<QByteArray>(this);
        connect(watcher, &QFutureWatcher<QByteArray>::finished, this, [watcher, this] {
            auto array = watcher->result();
            // here pokemon send be catched message to player
            emit beencatched(PokemongIcon(QVariant::fromValue(array), this->pokemonid), "NewPokemong");
            watcher->deleteLater();
            emit beendefeated();
        });
        watcher->setFuture(downloads(QString(baseurl).arg(pokemonid)));
    } else {
        QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher, this] {
            emit sendmessage(QString("Pokemon catched failed!"));
            emit attack(10);
        });
        watcher->setFuture(QtConcurrent::run([=] { QThread::sleep(2); }));
    }
}
// if attacked , to back or not back
void Enermy::beenAttack(int attacked)
{
    hps = attacked >= hps ? 0 : hps - attacked;
    hpline->lifeUpdate(hps);
    hplabel->setText(QString("hp = %1").arg(hps));
    update();  // dead
    if (hps == 0) {
        QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
        emit sendmessage(QString("Pokemon is defeated"));
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher, this] {
            watcher->deleteLater();
            emit beendefeated();
        });
        watcher->setFuture(QtConcurrent::run([=] { QThread::sleep(2); }));
    } else {
        emit sendmessage(QString("Pokemon cattack player!"));
        QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher, this] {
            auto a = QRandomGenerator::global()->bounded(30);
            watcher->deleteLater();
            emit attack(a);
        });
        watcher->setFuture(QtConcurrent::run([=] { QThread::sleep(2); }));
    }
}
