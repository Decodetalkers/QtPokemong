#include <mywidgets/mybattlemap.h>

#include "mybattlemap_internal.h"
#include "mybattlemap_p.h"
#include <QPainter>
#include <QTimer>
const QString grass = ":/resources/grass.jpg";

MyBattleMapPrivate::MyBattleMapPrivate(MyBattleMap *q)
    : q_ptr(q)
{
}

void MyBattleMapPrivate::init()
{
    Q_Q(MyBattleMap);

    mime = new MyBattleMapMime(q);
    enermy = new MyBattleMapEnermy(q);
    stateMachine = new MyBattleMapStateMachine(q, mime, enermy);
    stateMachine->start();
    QCoreApplication::processEvents();
}

MyBattleMapPrivate::~MyBattleMapPrivate() {}

MyBattleMap::MyBattleMap(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new MyBattleMapPrivate(this))
{
    d_func()->init();
    // QTimer *timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, [&] { update(); });
    // timer->start(1);
}
MyBattleMap::~MyBattleMap() {}
void MyBattleMap::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap image = QPixmap(grass).scaled(width(), height());
    painter.drawPixmap(0, 0, image);
}

void MyBattleMap::myAttack()
{
    Q_D(MyBattleMap);
    emit d->stateMachine->signalMimeAttack();
}
void MyBattleMap::enermyAttack()
{
    Q_D(MyBattleMap);
    emit d->stateMachine->signamAnermyAttack();
}
