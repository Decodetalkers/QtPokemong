#include "linerbar.h"
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
const QColor green = QColor(30,100,0);
Linerbar::Linerbar(QWidget *parent)
    : QWidget(parent)
{
    //[0] set the size
    setMinimumSize(600, 100);
}
// [1] a linerbar
void Linerbar::paintEvent(QPaintEvent *event)
{
    float len = life / 100.0;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QPainterPath path;
    path.addRoundedRect(QRectF(10, 10, width(), 50), 10, 10);
    painter.setPen(QPen(Qt::black, 10));
    painter.fillPath(path, Qt::blue);
    QPainterPath blood;
    blood.addRoundedRect(QRectF(10, 10, width() * len, 50), 10, 10);
    painter.fillPath(blood, green);
}
