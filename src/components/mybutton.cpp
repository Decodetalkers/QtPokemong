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

void MyButtonPrivate::init()
{
    Q_Q(MyButton);

    toggletrack = new MybuttonToggleTrack(q);
    // toggletrack->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    toggle = new MybuttonToggle(q);
    // toggle->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    stateMachine = new QStateMachine(q);

    offState = new QState;
    onState = new QState;

    stateMachine->addState(offState);
    stateMachine->addState(onState);
    stateMachine->setInitialState(offState);

    q->setCheckable(true);
    q->setChecked(false);
    // can be clicked once
    q->setAutoExclusive(true);
    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    offState->assignProperty(toggle, "shift", -4);
    offState->assignProperty(toggletrack, "trackColor", black);
    onState->assignProperty(toggle, "shift", 4);
    onState->assignProperty(toggletrack, "trackColor", green);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    // offState to onstate
    transition = new QSignalTransition(q, &MyButton::toggled);

    transition->setTargetState(onState);
    offState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(toggle);
    animation->setDuration(150);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(toggletrack);
    animation->setDuration(150);
    // animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    // onstate to offstate
    transition = new QSignalTransition(q, &MyButton::toggled);
    transition->setTargetState(offState);
    onState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(toggle);
    animation->setDuration(150);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(toggletrack);
    animation->setDuration(150);
    // animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    //

    stateMachine->start();
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
// void MyButton::mousePressEvent(QMouseEvent *event)
//{
//     setChecked(!isChecked());
// }
