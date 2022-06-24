#include "game.h"
#include "pokemengwidgets/linerbar.h"
#include <QAbstractItemModel>
#include <QDebug>
#include <QFutureWatcher>
#include <QHBoxLayout>
#include <QLabel>
#include <QListView>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QPushButton>
#include <QRandomGenerator>
#include <QScopedPointer>
#include <QStringListModel>
#include <QWidget>
// QT_BEGIN_NAMESPACE
// class QGridLayout;
// class QHBoxLayout;
// class QIMage;
// class QLabel;
// class QModelIndex;
// class QSlider;
// class QStackedWidget;
// class QVBoxLayout;
// QT_END_NAMESPACE

//#include <QTableView>

#include <QtConcurrent>
const QString baseurl = "https://raw.githubusercontent.com/PokeAPI/sprites/"
                        "master/sprites/pokemon/%1.png";
const QString loadinged = ":/resources/yousaki.jpg";

Switch::Switch(QWidget *parent, QLayout *mainlayout)
    : QWidget(parent)
{
    setLayout(mainlayout);
}

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
        QThread::sleep(1);
        return res;
    });
}
void Player::beenattack(int attack)
{
    yourturn = true;
    hps = attack >= hps ? 0 : hps - attack;
    hpline->lifeupdate(hps);
    hplabel->setText(QString("hp = %1").arg(hps));
    update();
    // dead
    if (hps == 0) {
        QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher, this] {
            watcher->deleteLater();
            yourturn = false;
            emit beendefeated();
        });
        watcher->setFuture(QtConcurrent::run([=] { QThread::sleep(2); }));
    }
}
void Player::reflash()
{
    hps = 100;
    hpline->lifeupdate(hps);
    hplabel->setText(QString("hp = %1").arg(hps));
    yourturn = true;
    update();
}
Player::Player(QWidget *parent)
    : QWidget(parent)
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
    mymodel = new QStringListModel(this);
    QStringList List;
    List << "Fir"
         << "Thu"
         << "Wesday";
    mymodel->setStringList(List);
    auto mylistview = new QListView();
    auto mylistview2 = new QListView();
    mylistview->setModel(mymodel);
    mylistview2->setModel(mymodel);
    selections->addTab(mylistview, "Second");
    selections->addTab(mylistview2, "Third");
    panel->addWidget(selections);
    QVBoxLayout *hp = new QVBoxLayout();
    {
        hpline = new Linerbar();
        // QSlider *hpline = new QSlider(Qt::Horizontal);
        // hpline->setRange(0, 100);
        // hpline->setValue(50);
        // hpline->setFixedWidth(600);
        // hpline->setEnabled(false);
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
        if (yourturn)
            emit attack(10);
        yourturn = false;
    });
    connect(cc, &QPushButton::clicked, this, [&] {
        mymodel->insertRow(mymodel->rowCount());
        auto index = mymodel->index(mymodel->rowCount() - 1, 0);
        mymodel->setData(index, "test");
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
Enermy::Enermy(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *panel = new QHBoxLayout();
    QVBoxLayout *hp = new QVBoxLayout();
    {
        hpline = new Linerbar();
        // QSlider *hpline = new QSlider(Qt::Horizontal);
        // hpline->setRange(0, 100);
        // hpline->setValue(50);
        // hpline->setEnabled(false);
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

void Enermy::loading()
{
    auto a = QRandomGenerator::global()->bounded(100);
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

void Enermy::reflash()
{
    hps = 100;
    hpline->lifeupdate(hps);
    hplabel->setText(QString("hp = %1").arg(hps));
    update();
    loading();
}
void Enermy::beenattack(int attacked)
{
    hps = attacked >= hps ? 0 : hps - attacked;
    hpline->lifeupdate(hps);
    hplabel->setText(QString("hp = %1").arg(hps));
    update();  // dead
    if (hps == 0) {
        QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher, this] {
            watcher->deleteLater();
            emit beendefeated();
        });
        watcher->setFuture(QtConcurrent::run([=] { QThread::sleep(2); }));
    } else {
        QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher, this] {
            auto a = QRandomGenerator::global()->bounded(30);
            watcher->deleteLater();
            emit attack(a);
        });
        watcher->setFuture(QtConcurrent::run([=] { QThread::sleep(2); }));
    }
}
