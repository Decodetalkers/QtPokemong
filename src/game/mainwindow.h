#pragma once

#include "game.h"
#include "pokemongwidgets/pokemongmap.h"
//#include "pokemengwidgets/pokemongtable.h"

#include <mywidgets/models/pokemongmodel.h>
#include <mywidgets/mybattlemap.h>

#include <QGSettings/QGSettings>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QStringListModel>
class GamePanel : public QWidget
{
    Q_OBJECT
public:
    GamePanel(QWidget *parent = nullptr, QSharedPointer<PokeMonModel> model = QSharedPointer<PokeMonModel>(new PokeMonModel));
    // void loadPlugins();
    void refresh();
public slots:
    void getWeather(QString weather);
    void messagesUpdate(QString message);

signals:
    void exit();

private:
    QStringListModel *m_messagemodel;
    MyBattleMap *m_battlemap;
    // QGridLayout *grid;
    Enermy *m_enermy;
    Player *m_player;

    // void catchpokemong(PokemongIcon, QString);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QSharedPointer<PokeMonModel> model = QSharedPointer<PokeMonModel>(new PokeMonModel));
    ~MainWindow();
private slots:
    void battle();

private:
    GamePanel *m_panel;
    PokemonMap *m_mainlay;
    QStackedWidget *m_aboveall;

    QTimer *m_timer;
    QGSettings *m_gsettings;
};
