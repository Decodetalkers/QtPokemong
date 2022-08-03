#include <interface/myinterface.h>
#include <interface/plugin.h>
#include <mywidgets/mybattlemap.h>

#include "game.h"
#include "mainwindow.h"
#include "pokemongwidgets/pokemongmap.h"
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
    m_enermy = new Enermy();
    root->addWidget(m_enermy);
    // grid = new QGridLayout;
    // grid->setAlignment(Qt::AlignmentFlag::AlignCenter);
    QPushButton *b1 = new QPushButton("a");
    connect(b1, &QPushButton::clicked, this, [&] { emit exit(); });

    QPushButton *a1 = new QPushButton("b");

    QHBoxLayout *middle = new QHBoxLayout();
    {
        m_battlemap = new MyBattleMap;
        m_battlemap->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_battlemap->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        middle->addWidget(m_battlemap);
        // loadPlugins();

        m_messagemodel = new QStringListModel(this);
        QStringList List;
        List << "Game Start";
        m_messagemodel->setStringList(List);
        QListView *mylistview = new QListView();
        mylistview->setModel(m_messagemodel);
        middle->addWidget(mylistview);
    }
    m_player = new Player(this, model);
    root->addLayout(middle);
    root->addWidget(m_player);
    // attack
    connect(m_player, &Player::attack, m_enermy, &Enermy::beenAttack);
    connect(m_player, &Player::attack, m_battlemap, &MyBattleMap::myAttack);
    connect(m_enermy, &Enermy::attack, m_player, &Player::beenAttack);
    connect(m_enermy, &Enermy::attack, m_battlemap, &MyBattleMap::enermyAttack);

    // defeated
    connect(m_player, &Player::beendefeated, this, [&] { emit exit(); });
    connect(m_enermy, &Enermy::beendefeated, this, [&] { emit exit(); });

    // catched
    connect(m_enermy, &Enermy::beencatched, m_player, &Player::updatePokemonodel);
    // try to catch
    connect(m_player, &Player::trycatch, m_enermy, &Enermy::trybecatched);

    // send message to the GamePanel
    connect(m_player, &Player::sendmessage, this, &GamePanel::messagesUpdate);
    connect(m_enermy, &Enermy::sendmessage, this, &GamePanel::messagesUpdate);
    setLayout(root);
}
void GamePanel::messagesUpdate(QString message)
{
    m_messagemodel->insertRow(m_messagemodel->rowCount());
    auto index = m_messagemodel->index(m_messagemodel->rowCount() - 1, 0);
    m_messagemodel->setData(index, message);
}
// TODO , weather will change the attack action
void GamePanel::getWeather(QString weather)
{
    m_messagemodel->insertRow(m_messagemodel->rowCount());
    auto index = m_messagemodel->index(m_messagemodel->rowCount() - 1, 0);
    m_messagemodel->setData(index, QString("Weather become %1").arg(weather));
}

// refresh the state of players
void GamePanel::refresh()
{
    m_enermy->refresh();
    m_player->refrash();
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
    m_aboveall = new QStackedWidget(this);
    m_panel = new GamePanel(this, model);
    m_aboveall->addWidget(m_panel);
    m_mainlay = new PokemonMap(this, model);
    // mainlay->installEventFilter(this);
    m_aboveall->addWidget(m_mainlay);
    m_aboveall->setCurrentIndex(1);
    setCentralWidget(m_aboveall);
    m_mainlay->setFocus();
    connect(m_panel, &GamePanel::exit, this, [&] { m_aboveall->setCurrentIndex(1); });
    connect(m_mainlay, &PokemonMap::MeetEnermy, this, [&] {
        // panel = new GamePanel(this);
        m_panel->refresh();
        m_aboveall->setCurrentIndex(0);
    });
    QDBusInterface *iface = new QDBusInterface(SERVICE_NAME, "/", "mime.example.test", QDBusConnection::sessionBus());
    m_timer = new QTimer(this);
    if (iface->isValid()) {
        connect(iface, SIGNAL(Weather(QString)), m_mainlay, SLOT(drawMessageUpdate(QString)));
        connect(iface, SIGNAL(Weather(QString)), m_panel, SLOT(getWeather(QString)));
        connect(iface, SIGNAL(MeetEnermy()), this, SLOT(battle()));
    } else {
        connect(m_timer, &QTimer::timeout, this, [&] {
            QDBusInterface *iface = new QDBusInterface(SERVICE_NAME, "/", "mime.example.test", QDBusConnection::sessionBus());
            if (iface->isValid()) {
                // get the weather of pokemeng
                connect(iface, SIGNAL(Weather(QString)), m_mainlay, SLOT(drawMessageUpdate(QString)));
                connect(iface, SIGNAL(Weather(QString)), m_panel, SLOT(getWeather(QString)));
                // get the meetenermy action
                connect(iface, SIGNAL(MeetEnermy()), this, SLOT(battle()));

                m_timer->stop();
            }
        });
        // every ten second tick once to get the message
        m_timer->start(10);
    }
}

// meet the enermy
void MainWindow::battle()
{
    int index = m_aboveall->currentIndex();
    if (index == 1) {
        m_panel->refresh();
        m_aboveall->setCurrentIndex(0);
    }
}
MainWindow::~MainWindow()
{
    delete m_panel;
    delete m_mainlay;
}
