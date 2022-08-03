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

    m_mime = new MyBattleMapMime(q);
    m_enermy = new MyBattleMapEnermy(q);
    m_stateMachine = new MyBattleMapStateMachine(q, m_mime, m_enermy);
    m_stateMachine->start();
    QCoreApplication::processEvents();
}

MyBattleMapPrivate::~MyBattleMapPrivate() {}

MyBattleMap::MyBattleMap(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new MyBattleMapPrivate(this))
{
    d_func()->init();
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
    emit d->m_stateMachine->signalMimeAttack();
}
void MyBattleMap::enermyAttack()
{
    Q_D(MyBattleMap);
    emit d->m_stateMachine->signamAnermyAttack();
}
