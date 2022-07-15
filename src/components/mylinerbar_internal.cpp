#include "mylinerbar_internal.h"
#include "mywidgets/mylinerbar.h"
#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QSignalTransition>
#include <QWidget>
const QColor green = QColor(30, 100, 0);

MyLinerBarStateMachine::MyLinerBarStateMachine(MyLinerBar *parent, MyLinerBarLife *mylife)
    : QStateMachine(parent)
    , life(100)
    , m_bar(parent)
    , m_life(mylife)
    , m_beforeState(new QState)
    , m_afterState(new QState)
{
    addState(m_beforeState);
    addState(m_afterState);

    setInitialState(m_beforeState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    transition = new QSignalTransition(this, &MyLinerBarStateMachine::attack);
    transition->setTargetState(m_afterState);
    m_beforeState->addTransition(transition);

    animation = new QPropertyAnimation(mylife, "deletedlife", this);
    animation->setDuration(420);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    QSequentialAnimationGroup *animationgroup = new QSequentialAnimationGroup;
    animationgroup->addAnimation(animation);
    animationgroup->addPause(400);
    transition->addAnimation(animationgroup);

    animation = new QPropertyAnimation(mylife, "life", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    QObject::connect(animationgroup, &QAnimationGroup::finished, m_beforeState, [&] {
        m_beforeState->assignProperty(m_life, "life", life);
        m_beforeState->assignProperty(m_life, "deletedlife", life);
    });
    transition = new QSignalTransition(animationgroup, &QAnimationGroup::finished);
    transition->setTargetState(m_beforeState);
    m_afterState->addTransition(transition);
    updatePropertyAssignment();
}
MyLinerBarStateMachine::~MyLinerBarStateMachine() {}
void MyLinerBarStateMachine::updatePropertyAssignment()
{
    m_beforeState->assignProperty(m_life, "life", life);
    m_beforeState->assignProperty(m_life, "deletedlife", life);

    m_afterState->assignProperty(m_life, "life", life);
    m_afterState->assignProperty(m_life, "deletedlife", life);
}
void MyLinerBarStateMachine::updateAfterAssignment(qreal deleted)
{
    if (deleted > life) {
        life = 0;
    } else {
        life -= deleted;
    }
    m_afterState->assignProperty(m_life, "life", life);
    m_afterState->assignProperty(m_life, "deletedlife", life);
}
void MyLinerBarStateMachine::rebase()
{
    life = 100;

    m_afterState->assignProperty(m_life, "life", life);
    m_afterState->assignProperty(m_life, "deletedlife", life);

    emit attack();
    // updatePropertyAssignment();
}
MyLinerBarLife::MyLinerBarLife(MyLinerBar *parent)
    : QWidget(parent)
    , m_linerbar(parent)
    , m_life(100)
    , m_deletedlife(100)
{
    Q_ASSERT(parent);
    parent->installEventFilter(this);
}
MyLinerBarLife::~MyLinerBarLife() {}
bool MyLinerBarLife::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(m_linerbar->rect());
    }
    return QWidget::eventFilter(obj, event);
}

void MyLinerBarLife::setDeletedlife(qreal life)
{
    m_deletedlife = life;
    update();
}
void MyLinerBarLife::setLife(qreal life)
{
    m_life = life;
    update();
}
void MyLinerBarLife::paintEvent(QPaintEvent *event)
{
    float len = m_life / 100.0;
    float lendelete = m_deletedlife / 100.0;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QPainterPath path;
    path.addRoundedRect(QRectF(0, 0, width() * lendelete, 50), 10, 10);
    painter.setPen(QPen(Qt::black, 10));
    painter.fillPath(path, Qt::blue);
    QPainterPath blood;
    blood.addRoundedRect(QRectF(0, 0, width() * len, 50), 10, 10);
    painter.fillPath(blood, green);
}
