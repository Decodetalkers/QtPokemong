#include <interface/myinterface.h>
#include <interface/plugin.h>

#include "game.h"
#include "mainwindow.h"
#include "pokemengwidgets/pokemengmap.h"
#include "pokemengwidgets/pokemongtable.h"

#include <QCoreApplication>
#include <QDBusInterface>
#include <QDebug>
#include <QDir>
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

GamePanel::GamePanel(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *root = new QVBoxLayout();
    enermy = new Enermy();
    root->addWidget(enermy);
    grid = new QGridLayout;
    grid->setAlignment(Qt::AlignmentFlag::AlignCenter);
    QPushButton *b1 = new QPushButton("a");
    connect(b1, &QPushButton::clicked, this, [&] { emit exit(); });

    // TODO , change it to battle map
    QPushButton *a1 = new QPushButton("b");
    QHBoxLayout *middle = new QHBoxLayout();
    {
        a1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        grid->addWidget(b1, 0, 0, 1, 1);
        grid->addWidget(a1, 0, 1, 1, 1);
        middle->addLayout(grid);
        loadPlugins();

        // make a model for the message
        messagemodel = new QStringListModel(this);
        QStringList List;
        List << "Game Start";
        messagemodel->setStringList(List);
        auto mylistview = new QListView();
        mylistview->setModel(messagemodel);
        middle->addWidget(mylistview);
    }
    player = new Player(this, QSharedPointer<PokeMonModel>(new PokeMonModel(this)));
    root->addLayout(middle);
    root->addWidget(player);
    // attack
    connect(player, &Player::attack, enermy, &Enermy::beenAttack);
    connect(enermy, &Enermy::attack, player, &Player::beenAttack);

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

// TODO move plugins to the map
void GamePanel::loadPlugins()
{
    QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
    if (!pluginsDir.cd("plugins"))
        return;
    int count = 0;
    foreach (QString filename, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(filename));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            // qDebug() << "gamma";
            auto interface = qobject_cast<QtPluginInterface *>(plugin);
            if (interface) {
                // qDebug() << "beta";
                grid->addWidget(interface->thebutton(), 2, count, 1, 1);
                count++;
            }
        }
    }
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // above the stack
    aboveall = new QStackedWidget(this);
    panel = new GamePanel(this);
    aboveall->addWidget(panel);
    mainlay = new PokemonMap(this);
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
