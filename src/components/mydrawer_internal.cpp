#include "mydrawer_internal.h"
#include <mywidgets/mydrawer.h>

#include <QPainter>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>
#include <QStateMachine>
MyDrawerStateMachine::MyDrawerStateMachine(MyDrawerWidget *drawer, MyDrawer *parent)
    : QStateMachine(parent)
    , m_drawer(drawer)
    , m_main(parent)
    , m_openingState(new QState)
    , m_openedState(new QState)
    , m_closingState(new QState)
    , m_closedState(new QState)
    , m_opacity(0)
{
    addState(m_openedState);
    addState(m_openingState);
    addState(m_closedState);
    addState(m_closingState);

    setInitialState(m_closedState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    // connect to closed to openning
    transition = new QSignalTransition(this, &MyDrawerStateMachine::signalOpen);
    transition->setTargetState(m_openingState);
    m_closedState->addTransition(transition);

    // set animation and add to transition
    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    // set animation and add to transition
    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    // finished to
    transition = new QSignalTransition(animation, &QPropertyAnimation::finished);
    transition->setTargetState(m_openedState);
    m_openingState->addTransition(transition);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    // go to closing
    transition = new QSignalTransition(this, &MyDrawerStateMachine::signalClose);
    transition->setTargetState(m_closingState);
    m_openingState->addTransition(transition);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    // go to closed
    transition = new QSignalTransition(animation, &QPropertyAnimation::finished);
    transition->setTargetState(m_closedState);
    m_closingState->addTransition(transition);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    transition = new QSignalTransition(this, &MyDrawerStateMachine::signalClose);
    transition->setTargetState(m_closingState);
    m_openedState->addTransition(transition);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, &QPropertyAnimation::finished);
    transition->setTargetState(m_closedState);
    m_closingState->addTransition(transition);

    updatePropertyAssignments();
    // transition = new QSignalTransition(animation, &QPropertyAnimation::finished);
}
MyDrawerStateMachine::~MyDrawerStateMachine() {}

void MyDrawerStateMachine::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    m_main->update();
}
void MyDrawerStateMachine::updatePropertyAssignments()
{
    const qreal closedOffset = -(m_drawer->width() + 32);

    m_closingState->assignProperty(m_drawer, "offset", closedOffset);
    m_closedState->assignProperty(m_drawer, "offset", closedOffset);

    m_closingState->assignProperty(this, "opacity", 0.3);
    m_closedState->assignProperty(this, "opacity", 0);

    m_openingState->assignProperty(m_drawer, "offset", 0);
    m_openedState->assignProperty(m_drawer, "offset", 0);
    m_openingState->assignProperty(this, "opacity", 0.4);
    m_openedState->assignProperty(this, "opacity", 0.7);
}

/*!
 *
 * @class MyDrawerWidget
 * @internal
 */

MyDrawerWidget::MyDrawerWidget(QWidget *parent)
    : MyOverlayWidget(parent)
    , m_offset(0)
{
}

MyDrawerWidget::~MyDrawerWidget() {}

void MyDrawerWidget::setOffset(int offset)
{
    m_offset = offset;
    QWidget *widget = parentWidget();
    if (widget) {
        setGeometry(widget->rect().translated(offset, 0));
    }
    update();
}

void MyDrawerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawRect(rect().adjusted(0, 0, -16, 0));

    QLinearGradient gradient(QPointF(width() - 16, 0), QPointF(width(), 0));
    gradient.setColorAt(0, QColor(0, 0, 0, 80));
    gradient.setColorAt(0.5, QColor(0, 0, 0, 20));
    gradient.setColorAt(1, QColor(0, 0, 0, 0));
    painter.setBrush(QBrush(gradient));

    painter.drawRect(width() - 16, 0, 16, height());
}

QRect MyDrawerWidget::overlayGeometry() const
{
    return MyOverlayWidget::overlayGeometry().translated(m_offset, 0);
}
