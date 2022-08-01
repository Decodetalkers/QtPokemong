#pragma once

#include "mywidgets/models/pokemongmodel.h"
#include <QGSettings/QGSettings>
#include <QWidget>
class Loading : public QWidget
{
    Q_OBJECT
public:
    explicit Loading(QWidget *parent = nullptr);

private:
    int m_dist = 0;
    QGSettings *m_gsettings;
    QList<PokemongIcon> icons;
};
