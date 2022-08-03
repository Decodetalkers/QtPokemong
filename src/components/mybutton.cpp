#include "mywidgets/mybutton.h"
#include "mybutton_p.h"
#include <mybutton_internal.h>

#include <QColor>
#include <QCoreApplication>
#include <QDebug>
#include <QEventTransition>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QStateMachine>

const QColor green = QColor(30, 100, 0);
const QColor black = QColor(0, 0, 0);

MyButtonPrivate::MyButtonPrivate(MyButton *q)
    : q_ptr(q)
{
}

MyButtonPrivate::~MyButtonPrivate() {}

/*
 * it is for init
 * for the begening
 */
void MyButtonPrivate::init()
{
    Q_Q(MyButton);

    m_toggletrack = new MybuttonToggleTrack(q);
    // toggletrack->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_toggle = new MybuttonToggle(q);
    // toggle->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_stateMachine = new QStateMachine(q);

    m_offState = new QState;
    m_onState = new QState;

    m_stateMachine->addState(m_offState);
    m_stateMachine->addState(m_onState);
    m_stateMachine->setInitialState(m_offState);

    q->setCheckable(true);
    q->setChecked(false);
    // can be clicked once
    q->setAutoExclusive(true);
    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_offState->assignProperty(m_toggle, "shift", -4);
    m_offState->assignProperty(m_toggletrack, "trackColor", black);
    m_onState->assignProperty(m_toggle, "shift", 4);
    m_onState->assignProperty(m_toggletrack, "trackColor", green);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    // offState to onstate
    transition = new QSignalTransition(q, &MyButton::toggled);

    transition->setTargetState(m_onState);
    m_offState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(m_toggle);
    animation->setDuration(150);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(m_toggletrack);
    animation->setDuration(150);
    // animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    // onstate to offstate
    transition = new QSignalTransition(q, &MyButton::toggled);
    transition->setTargetState(m_offState);
    m_onState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(m_toggle);
    animation->setDuration(150);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(m_toggletrack);
    animation->setDuration(150);
    // animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    //

    m_stateMachine->start();
    QCoreApplication::processEvents();
}

MyButton::MyButton(QWidget *parent)
    : QAbstractButton(parent)
    , d_ptr(new MyButtonPrivate(this))
{
    d_func()->init();
}
MyButton::~MyButton() {}

bool MyButton::event(QEvent *event)
{
    return QAbstractButton::event(event);
}
bool MyButton::eventFilter(QObject *obj, QEvent *event)
{
    return QAbstractButton::eventFilter(obj, event);
}

void MyButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}
