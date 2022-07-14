#pragma once

#include "pokemengwidgets/pokemengmap.h"
#include "pokemengwidgets/pokemongtable.h"
#include "game.h"

#include <mywidgets/mybattlemap.h>

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QStringListModel>
class GamePanel : public QWidget
{
    Q_OBJECT
public:
    GamePanel(QWidget *parent = nullptr);
    //void loadPlugins();
    void refresh();
public slots:
	void getWeather(QString weather);
	void messagesUpdate(QString message);
private:
	QStringListModel *messagemodel;
	MyBattleMap *battlemap;
    //QGridLayout *grid;
	Enermy *enermy;
	Player *player;

signals:
    void exit();
	//void catchpokemong(PokemongIcon, QString);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
	void battle();
private:
    GamePanel *panel;
    PokemonMap *mainlay;
    QStackedWidget *aboveall;

	QTimer *timer;
};
