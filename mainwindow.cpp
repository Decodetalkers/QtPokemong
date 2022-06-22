#include "mainwindow.h"
#include "game.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPluginLoader>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <interface/plugin.h>
#include "pokemengwidgets/pokemengmap.h"
GamePanel::GamePanel(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *root = new QVBoxLayout();
    root->addWidget(new Enermy());
    grid = new QGridLayout;
    grid->setAlignment(Qt::AlignmentFlag::AlignCenter);
    QPushButton *b1 = new QPushButton("a");
    connect(b1, &QPushButton::clicked, this, [&] { emit exit(); });
    QPushButton *a1 = new QPushButton("b");
    {
        a1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    grid->addWidget(b1, 0, 0, 1, 1);
    grid->addWidget(a1, 0, 1, 1, 1);
    loadPlugins();
	root->addWidget(new PokemonMap);
    root->addLayout(grid);
    root->addWidget(new Player());
    setLayout(root);
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
    mainlay = new QPushButton("start");
    aboveall->addWidget(mainlay);
    aboveall->setCurrentIndex(1);
    setCentralWidget(aboveall);

    connect(panel, &GamePanel::exit, this, [&] { aboveall->setCurrentIndex(1); });
    connect(mainlay, &QPushButton::clicked, this, [&] { aboveall->setCurrentIndex(0); });
}

MainWindow::~MainWindow() {}
