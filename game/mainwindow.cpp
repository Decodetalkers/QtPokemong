#include "mainwindow.h"
#include "game.h"
#include "pokemengwidgets/pokemengmap.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListView>
#include <QObject>
#include <QPluginLoader>
#include <QPushButton>
#include <QStackedWidget>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QWidget>
//#include "backendinterface.h"
#include <interface/myinterface.h>
#include <interface/plugin.h>
#include <QDBusInterface>
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

    QHBoxLayout *middle = new QHBoxLayout();
    {
        QPushButton *a1 = new QPushButton("b");
        {
            a1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }
        grid->addWidget(b1, 0, 0, 1, 1);
        grid->addWidget(a1, 0, 1, 1, 1);
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
    QDBusInterface *iface = new QDBusInterface(SERVICE_NAME, "/", "mime.example.test", QDBusConnection::sessionBus());

    //org::example::qtdbus::pingexample::ping *iface =
    //    new org::example::qtdbus::pingexample::ping(SERVICE_NAME, "/", QDBusConnection::sessionBus(), this);
	connect(iface, SIGNAL(weather(QString)),this, SLOT(getweather(QString)));
    setLayout(root);
}
void GamePanel::getweather(QString weather)
{
    qDebug() << weather;
	mymodel->insertRow(mymodel->rowCount());
        auto index = mymodel->index(mymodel->rowCount() - 1, 0);
        mymodel->setData(index, weather);
}
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
}

MainWindow::~MainWindow()
{
    delete panel;
    delete mainlay;
}
