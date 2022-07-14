#pragma once

//#include "mywidgets/mydrawer.h"
#include <mywidgets/mydrawer.h>

#include <QPaintEvent>
#include <QRandomGenerator>
#include <QWidget>
class PokemonMap : public QWidget
{
    Q_OBJECT
public:
    PokemonMap(QWidget *parent = nullptr);

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
    MyDrawer *mydrawer;
    QPoint playerposition = {0, 0};
    bool hasmessage = false;
    QString message = "";
};

