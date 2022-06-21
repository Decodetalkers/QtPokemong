#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
class GamePanel : public QWidget
{
    Q_OBJECT
public:
    GamePanel(QWidget *parent = nullptr);
    void loadPlugins();

private:
    QGridLayout *grid;
signals:
    void exit();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    GamePanel *panel;
    QPushButton *mainlay;
    QStackedWidget *aboveall;
};
#endif  // MAINWINDOW_H
