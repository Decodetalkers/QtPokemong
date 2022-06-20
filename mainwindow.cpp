#include "mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QDir>
#include <QPluginLoader>
#include <QCoreApplication>
#include <interface/plugin.h>
#include <QObject>
#include <QDebug>
Temp::Temp(QWidget *parent) : QWidget(parent) {
  grid = new QGridLayout;
  QPushButton *b1 = new QPushButton("a");
  QPushButton *a1 = new QPushButton("b");
  grid->addWidget(b1, 0, 0, 1, 1);
  grid->addWidget(a1, 0, 1, 1, 1);
	loadPlugins();
  setLayout(grid);
}
void Temp::loadPlugins() {
	QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
	if(!pluginsDir.cd("plugins")) return;
	foreach( QString filename, pluginsDir.entryList(QDir::Files))
	{
		qDebug() << "test";
		qDebug() << pluginsDir.absoluteFilePath(filename);
		QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(filename));
		if (!pluginLoader.load()) {
			qDebug() << pluginLoader.errorString();
		}
		QObject *plugin = pluginLoader.instance();
		if (plugin) {
			qDebug() << "gamma";
			auto interface = qobject_cast<QtPluginInterface*>(plugin);
			if (interface) {
				qDebug() << "beta";
				grid->addWidget(interface->thebutton(),2,0,1,1);
			}
		}
	}
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  Temp *temp = new Temp();
  setCentralWidget(temp);
}

MainWindow::~MainWindow() {}
