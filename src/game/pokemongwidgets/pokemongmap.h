#pragma once

//#include "mywidgets/mydrawer.h"
#include <mywidgets/mydrawer.h>

#include <QPaintEvent>
#include <QRandomGenerator>
#include <QWidget>
#include <mywidgets/models/pokemongmodel.h>
class PokemonMap : public QWidget
{
    Q_OBJECT
public:
    PokemonMap(QWidget *parent = nullptr, QSharedPointer<PokeMonModel> model = QSharedPointer<PokeMonModel>(new PokeMonModel));
#ifdef TEST
    inline QPoint position() const;
    inline void reset();
#endif  //
public slots:
    void drawMessageUpdate(QString weather);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
signals:
    void MeetEnermy();

private:
    QRandomGenerator *qrand;
    QPoint enermys[16] = {
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
    };
    QSharedPointer<PokeMonModel> m_model;
    MyDrawer *mydrawer;
    QPoint playerposition = {0, 0};
    bool hasmessage = false;
    QString message = "";
};
#ifdef TEST
inline QPoint PokemonMap::position() const
{
    return playerposition;
}
inline void PokemonMap::reset()
{
    playerposition = {0, 0};
}
#endif
