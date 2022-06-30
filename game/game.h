#ifndef GAME_H
#define GAME_H

#include "pokemengwidgets/linerbar.h"
#include "pokemengwidgets/pokemongtable.h"
//#include <QLabel>
#include <QNetworkAccessManager>
#include <QStringListModel>
QT_BEGIN_NAMESPACE
class QLabel;
class QHBoxLayout;
QT_END_NAMESPACE
#include <QWidget>
class Switch : public QWidget
{
    Q_OBJECT
public:
    Switch(QWidget *parent , QLayout *mainlayout);
};
class Player : public QWidget
{
    Q_OBJECT
public:
    Player(QWidget *parent = nullptr);
    void reflash();
signals:
	/*
	 * @brief attacked
	 * @param how much is attacked
	 */
    void attack(int);
    void beendefeated();
public slots:
    void beenattack(int attack);
	void updatepokemonmodel(PokemongIcon pokemon, QString name);
private:
    QLabel *player;
    QLabel *hplabel;
    Linerbar *hpline;
    void download(const QUrl url);
    int hps = 100;
    bool yourturn = true;
	QStringListModel *mymodel;
	PokeMonModel *pokemonmodel;
};

class Enermy : public QWidget
{
    Q_OBJECT
public:
    Enermy(QWidget *parent = nullptr);
    void reflash();
signals:
    void attack(int);
	void beencatched(PokemongIcon pokemon, QString name);
    void beendefeated();
public slots:
    void beenattack(int attack);
	void trybecatched();
private:
    QLabel *enermy;
    QLabel *hplabel;
	int pokemonid = 0;
    Linerbar *hpline;
    void loading();
    int hps = 100;
};
#endif  // !GAME_H
