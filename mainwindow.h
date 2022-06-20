#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

class Temp :public QWidget {
	Q_OBJECT
public:
		Temp(QWidget *parent = nullptr);
		void loadPlugins();
private:
		QGridLayout *grid;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
