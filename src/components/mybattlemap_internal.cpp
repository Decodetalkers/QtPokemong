#include <mywidgets/mybattlemap.h>

#include "mybattlemap_internal.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>
#include <QStateMachine>
const QString playerRed = ":/resources/red.png";

MyBattleMapStateMachine::MyBattleMapStateMachine(MyBattleMap *battlemap, MyBattleMapMime *mypokemong, MyBattleMapEnermy *enermy)
    : QStateMachine(battlemap)
    , m_battlemap(battlemap)
    , m_mime(mypokemong)
    , m_enermy(enermy)
    , m_normalState(new QState)
    , m_enermyattackingState(new QState)
    , m_meattackingState(new QState)
{
    addState(m_normalState);
    addState(m_enermyattackingState);
    addState(m_meattackingState);

    setInitialState(m_normalState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    //[1]
    // set from normal to attacking
    transition = new QSignalTransition(this, &MyBattleMapStateMachine::signalMimeAttack);
    transition->setTargetState(m_meattackingState);
    m_normalState->addTransition(transition);

    animation = new QPropertyAnimation(m_mime, "positionx", this);
    animation->setDuration(420);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(m_mime, "positiony", this);
    animation->setDuration(420);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);
    // end attack

    // start staying for sometime
    transition = new QSignalTransition(animation, &QPropertyAnimation::finished);
    transition->setTargetState(m_meattackingState);
    m_meattackingState->addTransition(transition);

    animation = new QPropertyAnimation(m_mime, "positionx", this);
    animation->setDuration(100);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(m_mime, "positiony", this);
    animation->setDuration(100);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);
    // end back

    // start back
    transition = new QSignalTransition(animation, &QPropertyAnimation::finished);
    transition->setTargetState(m_normalState);
    m_meattackingState->addTransition(transition);

    animation = new QPropertyAnimation(m_mime, "positionx", this);
    animation->setDuration(420);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(m_mime, "positiony", this);
    animation->setDuration(420);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);
    // end back

    //[2]
    // set from normal to anermyattacking
    transition = new QSignalTransition(this, &MyBattleMapStateMachine::signamAnermyAttack);
    transition->setTargetState(m_enermyattackingState);
    m_normalState->addTransition(transition);

    animation = new QPropertyAnimation(m_enermy, "positionx", this);
    animation->setDuration(420);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(m_enermy, "positiony", this);
    animation->setDuration(420);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);
    // end attack

    // start staying
    transition = new QSignalTransition(animation, &QPropertyAnimation::finished);
    transition->setTargetState(m_enermyattackingState);
    m_enermyattackingState->addTransition(transition);

    animation = new QPropertyAnimation(m_enermy, "positionx", this);
    animation->setDuration(100);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(m_enermy, "positiony", this);
    animation->setDuration(100);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);
    // end staying

    // start back
    transition = new QSignalTransition(animation, &QPropertyAnimation::finished);
    transition->setTargetState(m_normalState);
    m_enermyattackingState->addTransition(transition);

    animation = new QPropertyAnimation(m_enermy, "positionx", this);
    animation->setDuration(420);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(m_enermy, "positiony", this);
    animation->setDuration(420);
    animation->setEasingCurve(QEasingCurve::OutCurve);
    transition->addAnimation(animation);
    // end back
    updatePropertyAssignment();
}

void MyBattleMapStateMachine::updatePropertyAssignment()
{
    m_normalState->assignProperty(m_mime, "positionx", 0);
    m_normalState->assignProperty(m_mime, "positiony", 0.9);
    m_normalState->assignProperty(m_enermy, "positionx", 0.9);
    m_normalState->assignProperty(m_enermy, "positiony", 0);

    m_meattackingState->assignProperty(m_mime, "positionx", 0.6);
    m_meattackingState->assignProperty(m_mime, "positiony", 0.3);
    m_meattackingState->assignProperty(m_enermy, "positionx", 0.9);
    m_meattackingState->assignProperty(m_enermy, "positiony", 0);

    m_enermyattackingState->assignProperty(m_mime, "positionx", 0);
    m_enermyattackingState->assignProperty(m_mime, "positiony", 0.9);
    m_enermyattackingState->assignProperty(m_enermy, "positionx", 0.3);
    m_enermyattackingState->assignProperty(m_enermy, "positiony", 0.6);
}
MyBattleMapStateMachine::~MyBattleMapStateMachine() {}

// allow changed
MyBattleMapMime::MyBattleMapMime(MyBattleMap *parent)
    : QWidget(parent)
    , m_map(parent)
    , m_x(0)
    , m_y(0)
{
    Q_ASSERT(parent);
    parent->installEventFilter(this);
}

void MyBattleMapMime::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap image = QPixmap(playerRed).scaled(width() / 10, height() / 10);
    painter.drawPixmap(width() * m_x, height() * m_y, image);
}

MyBattleMapMime::~MyBattleMapMime() {}

void MyBattleMapMime::setPositionX(const qreal positionx)
{
    m_x = positionx;
    update();
}
void MyBattleMapMime::setPositionY(const qreal positiony)
{
    m_y = positiony;
    update();
}
bool MyBattleMapMime::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(m_map->rect());
    }
    return QWidget::eventFilter(obj, event);
}
MyBattleMapEnermy::MyBattleMapEnermy(MyBattleMap *parent)
    : QWidget(parent)
    , m_map(parent)
    , m_x(0.9)
    , m_y(0.9)
{
    Q_ASSERT(parent);
    parent->installEventFilter(this);
}

MyBattleMapEnermy::~MyBattleMapEnermy() {}

void MyBattleMapEnermy::setPositionX(const qreal positionx)
{
    m_x = positionx;
    update();
}
void MyBattleMapEnermy::setPositionY(const qreal positiony)
{
    m_y = positiony;
    update();
}
void MyBattleMapEnermy::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap image = QPixmap(playerRed).scaled(width() / 10, height() / 10);
    painter.drawPixmap(width() * m_x, height() * m_y, image);
}
bool MyBattleMapEnermy::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(m_map->rect());
    }
    return QWidget::eventFilter(obj, event);
}
