#include <interface/myinterface.h>
#include <interface/plugin.h>
#include <mywidgets/mybattlemap.h>

#include "game.h"
#include "mainwindow.h"
#include "pokemengwidgets/pokemengmap.h"
//#include "pokemengwidgets/pokemongtable.h"

#include <QCoreApplication>
#include <QDBusInterface>
#include <QDebug>
#include <QDir>
#include <QGSettings/QGSettings>
#include <QPluginLoader>
#include <QSharedPointer>
#include <QStringListModel>
#include <QtWidgets>
QT_BEGIN_NAMESPACE
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QStackedWidget;
class QListView;
class QTimer;
class QVBoxLayout;
QT_END_NAMESPACE

GamePanel::GamePanel(QWidget *parent, QSharedPointer<PokeMonModel> model)
    : QWidget(parent)
{
    QVBoxLayout *root = new QVBoxLayout();
    enermy = new Enermy();
    root->addWidget(enermy);
    // grid = new QGridLayout;
    // grid->setAlignment(Qt::AlignmentFlag::AlignCenter);
    QPushButton *b1 = new QPushButton("a");
    connect(b1, &QPushButton::clicked, this, [&] { emit exit(); });

    QPushButton *a1 = new QPushButton("b");

    QHBoxLayout *middle = new QHBoxLayout();
    {
        battlemap = new MyBattleMap;
        battlemap->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        battlemap->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        middle->addWidget(battlemap);
        // loadPlugins();

        messagemodel = new QStringListModel(this);
        QStringList List;
        List << "Game Start";
        messagemodel->setStringList(List);
        QListView *mylistview = new QListView();
        mylistview->setModel(messagemodel);
        middle->addWidget(mylistview);
    }
    player = new Player(this, model);
    root->addLayout(middle);
    root->addWidget(player);
    // attack
    connect(player, &Player::attack, enermy, &Enermy::beenAttack);
    connect(player, &Player::attack, battlemap, &MyBattleMap::myAttack);
    connect(enermy, &Enermy::attack, player, &Player::beenAttack);
    connect(enermy, &Enermy::attack, battlemap, &MyBattleMap::enermyAttack);

    // defeated
    connect(player, &Player::beendefeated, this, [&] { emit exit(); });
    connect(enermy, &Enermy::beendefeated, this, [&] { emit exit(); });

    // catched
    connect(enermy, &Enermy::beencatched, player, &Player::updatePokemonodel);
    // try to catch
    connect(player, &Player::trycatch, enermy, &Enermy::trybecatched);

    // send message to the GamePanel
    connect(player, &Player::sendmessage, this, &GamePanel::messagesUpdate);
    connect(enermy, &Enermy::sendmessage, this, &GamePanel::messagesUpdate);
    setLayout(root);
}
void GamePanel::messagesUpdate(QString message)
{
    messagemodel->insertRow(messagemodel->rowCount());
    auto index = messagemodel->index(messagemodel->rowCount() - 1, 0);
    messagemodel->setData(index, message);
}
// TODO , weather will change the attack action
void GamePanel::getWeather(QString weather)
{
    messagemodel->insertRow(messagemodel->rowCount());
    auto index = messagemodel->index(messagemodel->rowCount() - 1, 0);
    messagemodel->setData(index, QString("Weather become %1").arg(weather));
}

// refresh the state of players
void GamePanel::refresh()
{
    enermy->refresh();
    player->refrash();
    update();
}

MainWindow::MainWindow(QWidget *parent, QSharedPointer<PokeMonModel> model)
    : QMainWindow(parent)
{
    if (QGSettings::isSchemaInstalled("apps.eightplus.pokemongame")) {
        m_gsettings = new QGSettings("apps.eightplus.pokemongame");
        connect(m_gsettings, &QGSettings::changed, this, [=](const QString &key) {
            if (key == "weather") {
                qDebug() << "changed";
            }
        });
    }
    if (model->get_ids().size() == 0) {
        // realize the models
        // auto model = QSharedPointer<PokeMonModel>(new PokeMonModel(this));
        QList<PokemongIcon> icons;
        icons << PokemongIcon();
        QList<QString> names;
        names << "shadoxi";
        // pokemonmodel = new PokeMonModel(this);
        model->populateData(icons, names);
    }
    // above the stack
    aboveall = new QStackedWidget(this);
    panel = new GamePanel(this, model);
    aboveall->addWidget(panel);
    mainlay = new PokemonMap(this, model);
    // mainlay->installEventFilter(this);
    aboveall->addWidget(mainlay);
    aboveall->setCurrentIndex(1);
    setCentralWidget(aboveall);
    mainlay->setFocus();
    connect(panel, &GamePanel::exit, this, [&] { aboveall->setCurrentIndex(1); });
    connect(mainlay, &PokemonMap::MeetEnermy, this, [&] {
        // panel = new GamePanel(this);
        panel->refresh();
        aboveall->setCurrentIndex(0);
    });
    QDBusInterface *iface = new QDBusInterface(SERVICE_NAME, "/", "mime.example.test", QDBusConnection::sessionBus());
    timer = new QTimer(this);
    if (iface->isValid()) {
        connect(iface, SIGNAL(Weather(QString)), mainlay, SLOT(drawMessageUpdate(QString)));
        connect(iface, SIGNAL(Weather(QString)), panel, SLOT(getWeather(QString)));
        connect(iface, SIGNAL(MeetEnermy()), this, SLOT(battle()));
    } else {
        connect(timer, &QTimer::timeout, this, [&] {
            QDBusInterface *iface = new QDBusInterface(SERVICE_NAME, "/", "mime.example.test", QDBusConnection::sessionBus());
            if (iface->isValid()) {
                // get the weather of pokemeng
                connect(iface, SIGNAL(Weather(QString)), mainlay, SLOT(drawMessageUpdate(QString)));
                connect(iface, SIGNAL(Weather(QString)), panel, SLOT(getWeather(QString)));
                // get the meetenermy action
                connect(iface, SIGNAL(MeetEnermy()), this, SLOT(battle()));

                timer->stop();
            }
        });
        // every ten second tick once to get the message
        timer->start(10);
    }
}

// meet the enermy
void MainWindow::battle()
{
    int index = aboveall->currentIndex();
    if (index == 1) {
        panel->refresh();
        aboveall->setCurrentIndex(0);
    }
}
MainWindow::~MainWindow()
{
    delete panel;
    delete mainlay;
}
