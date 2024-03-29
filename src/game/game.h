#pragma once

#include <mywidgets/models/pokemongmodel.h>
#include <mywidgets/mylinerbar.h>

#include <QNetworkAccessManager>
#include <QSharedPointer>
#include <QStringListModel>
// use namespace to import these
QT_BEGIN_NAMESPACE
class QLabel;
class QHBoxLayout;
QT_END_NAMESPACE
#include <QWidget>
class Switch : public QWidget
{
    Q_OBJECT
public:
    Switch(QWidget *parent, QLayout *mainlayout);
};
class Player : public QWidget
{
    Q_OBJECT
public:
    Player(QWidget *parent = nullptr, QSharedPointer<PokeMonModel> model = QSharedPointer<PokeMonModel>(new PokeMonModel()));
    void refrash();
signals:
    /*
     * @brief attacked
     * @param signal
     */
    void attack(int);
    /* @brief beendefeated
     * @param signal
     */
    void beendefeated();
    /*
     * @brief try to catch the pokemon
     * @param signal
     */
    void trycatch();
    void sendmessage(const QString &message);
public slots:
    void beenAttack(int attack);
    void updatePokemonodel(PokemongIcon pokemon, QString name);

private:
    void download(const QUrl url);
    QLabel *player;
    QLabel *hplabel;
    MyLinerBar *hpline;
    int hps = 100;
    bool yourturn = true;
    QSharedPointer<PokeMonModel> pokemonmodel;
};

class Enermy : public QWidget
{
    Q_OBJECT
public:
    Enermy(QWidget *parent = nullptr);
    void refresh();
signals:
    void attack(int);
    void beencatched(PokemongIcon pokemon, QString name);
    void beendefeated();
    void sendmessage(const QString &message);
public slots:
    void beenAttack(int attack);
    void trybecatched();

private:
    QLabel *enermy;
    QLabel *hplabel;
    int pokemonid = 0;
    MyLinerBar *hpline;
    void loading();
    int hps = 100;
};
