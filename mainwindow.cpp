#include "mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QGridLayout>
#include <QObject>
#include <QPluginLoader>
#include <QPushButton>
#include <QWidget>
#include <interface/plugin.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "game.h"
Temp::Temp(QWidget *parent) : QWidget(parent) {
	QVBoxLayout *root = new QVBoxLayout();
	root->addWidget(new Enermy());
  grid = new QGridLayout;
	grid->setAlignment(Qt::AlignmentFlag::AlignCenter);
  QPushButton *b1 = new QPushButton("a");
  QPushButton *a1 = new QPushButton("b");
  grid->addWidget(b1, 0, 0, 1, 1);
  grid->addWidget(a1, 0, 1, 1, 1);
  loadPlugins();
	root->addLayout(grid);
	root->addWidget(new Player());
  setLayout(root);
}
void Temp::loadPlugins() {
  QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
  if (!pluginsDir.cd("plugins"))
    return;
	int count = 0;
  foreach (QString filename, pluginsDir.entryList(QDir::Files)) {
    //qDebug() << "test";
    //qDebug() << pluginsDir.absoluteFilePath(filename);
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(filename));
    //if (!pluginLoader.load()) {
    //  qDebug() << pluginLoader.errorString();
    //}
    QObject *plugin = pluginLoader.instance();
    if (plugin) {
      //qDebug() << "gamma";
      auto interface = qobject_cast<QtPluginInterface *>(plugin);
      if (interface) {
        //qDebug() << "beta";
        grid->addWidget(interface->thebutton(), 2, count, 1, 1);
				count++;
      }
    }
  }
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  Temp *temp = new Temp();
  setCentralWidget(temp);
}

MainWindow::~MainWindow() {}
