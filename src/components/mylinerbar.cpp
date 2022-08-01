#include "mylinerbar_internal.h"
#include "mylinerbar_p.h"
#include <mywidgets/mylinerbar.h>

#include <QCoreApplication>
#include <QDebug>
MyLinerBarPrivate::MyLinerBarPrivate(MyLinerBar *q)
    : q_ptr(q)
{
}

void MyLinerBarPrivate::init()
{
    Q_Q(MyLinerBar);
    life = new MyLinerBarLife(q);
    statemachine = new MyLinerBarStateMachine(q, life);
    statemachine->start();
    QCoreApplication::processEvents();
}
MyLinerBarPrivate::~MyLinerBarPrivate(){};

MyLinerBar::MyLinerBar(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new MyLinerBarPrivate(this))
{
    d_func()->init();
    setMinimumWidth(500);
}

void MyLinerBar::damage(qreal damage)
{
    Q_D(MyLinerBar);
    d->statemachine->updateAfterAssignment(damage);
    emit d->statemachine->attack();
}
void MyLinerBar::rebase()
{
    Q_D(MyLinerBar);
    d->statemachine->rebase();
}
void MyLinerBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QPainterPath path;
    path.addRoundedRect(QRectF(0, 0, width(), 50), 10, 10);
    painter.setPen(QPen(Qt::black, 10));
    painter.fillPath(path, Qt::darkGray);
}
MyLinerBar::~MyLinerBar() {}
#if TEST
qreal MyLinerBar::life() const
{
    Q_D(const MyLinerBar);
    return d_func()->statemachine->getlife();
}
#endif  // TEST
