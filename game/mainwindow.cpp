#include "mainwindow.h"
#include "game.h"
#include "pokemengwidgets/pokemengmap.h"
#include <QCoreApplication>
#include <QDBusInterface>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QPluginLoader>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QWidget>
#include <QtWidgets>
#include <interface/myinterface.h>
#include <interface/plugin.h>
QT_BEGIN_NAMESPACE
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QStackedWidget;
class QListView;
class QTimer;
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

    QPushButton *a1 = new QPushButton("b");
    QHBoxLayout *middle = new QHBoxLayout();
    {
        a1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        grid->addWidget(b1, 0, 0, 1, 1);
        grid->addWidget(a1, 0, 1, 1, 1);
        // connect(a1, &QPushButton::clicked, this, [&] {
        //	emit catchpokemong(PokemongIcon(), "ss");
        // });
        middle->addLayout(grid);
        loadPlugins();

        mymodel = new QStringListModel(this);
        QStringList List;
        List << "Fir"
             << "Thu"
             << "Wesday";
        mymodel->setStringList(List);
        auto mylistview = new QListView();
        mylistview->setModel(mymodel);
        middle->addWidget(mylistview);
    }
    // root->addWidget(new PokemonMap);
    // root->addLayout(grid);
    player = new Player();
    root->addLayout(middle);
    root->addWidget(player);
    connect(player, &Player::attack, enermy, &Enermy::beenattack);
    connect(enermy, &Enermy::attack, player, &Player::beenattack);
    connect(player, &Player::beendefeated, this, [&] { emit exit(); });
    connect(enermy, &Enermy::beendefeated, this, [&] { emit exit(); });
    connect(enermy, &Enermy::beencatched, player, &Player::updatepokemonmodel);
    connect(player, &Player::trycatch, enermy, &Enermy::trybecatched);
    connect(player, &Player::sendmessage, this, &GamePanel::messagesupdate);
    connect(enermy, &Enermy::sendmessage, this, &GamePanel::messagesupdate);
    // connect(a1, &QPushButton::clicked, enermy, &Enermy::trybecatched);
    setLayout(root);
}
void GamePanel::messagesupdate(QString message)
{
    mymodel->insertRow(mymodel->rowCount());
    auto index = mymodel->index(mymodel->rowCount() - 1, 0);
    mymodel->setData(index, message);
}
// TODO , weather will change the attack action
void GamePanel::getweather(QString weather)
{
    // qDebug() << weather;
    mymodel->insertRow(mymodel->rowCount());
    auto index = mymodel->index(mymodel->rowCount() - 1, 0);
    mymodel->setData(index, QString("Weather become %1").arg(weather));
}

// refresh the state of players
void GamePanel::refresh()
{
    enermy->reflash();
    player->reflash();
    update();
}
void GamePanel::loadPlugins()
{
    QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
    if (!pluginsDir.cd("plugins"))
        return;
    int count = 0;
    foreach (QString filename, pluginsDir.entryList(QDir::Files)) {
        // qDebug() << "test";
        // qDebug() << pluginsDir.absoluteFilePath(filename);
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(filename));
        // if (!pluginLoader.load()) {
        //   qDebug() << pluginLoader.errorString();
        // }
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
    connect(mainlay, &PokemonMap::meetenermy, this, [&] {
        // panel = new GamePanel(this);
        panel->refresh();
        aboveall->setCurrentIndex(0);
    });
    QDBusInterface *iface = new QDBusInterface(SERVICE_NAME, "/", "mime.example.test", QDBusConnection::sessionBus());
    timer = new QTimer(this);
    if (iface->isValid()) {
        connect(iface, SIGNAL(weather(QString)), panel, SLOT(getweather(QString)));
    } else {
        connect(timer, &QTimer::timeout, this, [&] {
            QDBusInterface *iface = new QDBusInterface(SERVICE_NAME, "/", "mime.example.test", QDBusConnection::sessionBus());
            if (iface->isValid()) {
                // get the weather of pokemeng
                connect(iface, SIGNAL(weather(QString)), panel, SLOT(getweather(QString)));
                // get the meetenermy action
                connect(iface, SIGNAL(meetenermy()), this, SLOT(battle()));
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
