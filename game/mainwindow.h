#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pokemengwidgets/pokemengmap.h"
#include "game.h"
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
    void refresh();

private:
    QGridLayout *grid;
	Enermy *enermy;
	Player *player;
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
    PokemonMap *mainlay;
    QStackedWidget *aboveall;
};
#endif  // MAINWINDOW_H
