#include <mywidgets/mypopupwindow.h>

#include "mypopupwindow_internal.h"
#include "mypopupwindow_p.h"

#include <QCoreApplication>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPropertyAnimation>
#include <QStackedLayout>
#include <QStateMachine>
#include <QMouseEvent>
#include <QVBoxLayout>
/*!
 * @class MyPopupwindowPrivate
 * @internal
 */

MyPopWindowPrivate::MyPopWindowPrivate(MyPopWindow *q)
    : q_ptr(q)
{
}

MyPopWindowPrivate::~MyPopWindowPrivate() {}

void MyPopWindowPrivate::init()
{
    Q_Q(MyPopWindow);

    m_dialogWindow = new MyPopWindowDialog(q);
    m_proxyStack = new QStackedLayout;
    m_stateMachine = new QStateMachine(q);
    m_proxy = new MyPopWindowProxy(m_dialogWindow, m_proxyStack, q);

    QVBoxLayout *layout = new QVBoxLayout;
    q->setLayout(layout);

    m_widget = new QWidget;
    m_widget->setLayout(m_proxyStack);
    m_widget->setMinimumWidth(400);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 200));
    effect->setBlurRadius(64);
    effect->setOffset(0, 13);
    m_widget->setGraphicsEffect(effect);

    layout->addWidget(m_widget);
    layout->setAlignment(m_widget, Qt::AlignCenter);

    m_proxyStack->addWidget(m_dialogWindow);
    m_proxyStack->addWidget(m_proxy);
    m_proxyStack->setCurrentIndex(1);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QState *hiddenState = new QState;
    QState *visibleState = new QState;

    m_stateMachine->addState(hiddenState);
    m_stateMachine->addState(visibleState);
    m_stateMachine->setInitialState(hiddenState);

    MyStateTransition *transiton;
    transiton = new MyStateTransition(MyTransitionType::ShowDialog);
    transiton->setTargetState(visibleState);
    hiddenState->addTransition(transiton);

    transiton = new MyStateTransition(MyTransitionType::HideDialog);
    transiton->setTargetState(hiddenState);
    visibleState->addTransition(transiton);

    visibleState->assignProperty(m_proxy, "opacity", 1);
    visibleState->assignProperty(effect, "color", QColor(0, 0, 0, 200));
    visibleState->assignProperty(m_dialogWindow, "offset", 0);
    hiddenState->assignProperty(m_proxy, "opacity", 0);
    hiddenState->assignProperty(effect, "color", QColor(0, 0, 0, 0));
    hiddenState->assignProperty(m_dialogWindow, "offset", 200);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(m_proxy, "opacity", q);
    animation->setDuration(280);
    m_stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(effect, "color", q);
    animation->setDuration(280);
    m_stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(m_dialogWindow, "offset", q);
    animation->setDuration(280);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    m_stateMachine->addDefaultAnimation(animation);

    QObject::connect(visibleState, &QState::propertiesAssigned, m_proxy, &MyPopWindowProxy::makeOpaque);
    QObject::connect(hiddenState, &QState::propertiesAssigned, m_proxy, &MyPopWindowProxy::makeTransparent);

    m_stateMachine->start();
    QCoreApplication::processEvents();
}

MyPopWindow::MyPopWindow(QWidget *parent)
    : MyOverlayWidget(parent)
    , d_ptr(new MyPopWindowPrivate(this))
{
    d_func()->init();
}

MyPopWindow::~MyPopWindow() {}

QLayout *MyPopWindow::windowLayout() const
{
    Q_D(const MyPopWindow);
    return d->m_dialogWindow->layout();
}

void MyPopWindow::setWindowLayout(QLayout *layout)
{
    Q_D(MyPopWindow);

    d->m_dialogWindow->setLayout(layout);
}

void MyPopWindow::showDialog()
{
    Q_D(MyPopWindow);
    d->m_stateMachine->postEvent(new MyTransitionEvent(MyTransitionType::ShowDialog));
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    raise();
}
void MyPopWindow::hideDialog()
{
    Q_D(MyPopWindow);
    d->m_stateMachine->postEvent(new MyTransitionEvent(MyTransitionType::HideDialog));
    setAttribute(Qt::WA_TransparentForMouseEvents);
    d->m_proxyStack->setCurrentIndex(1);
}
void MyPopWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(MyPopWindow);

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.setOpacity(d->m_proxy->opacity() / 2.4);
    painter.drawRect(rect());
}
bool MyPopWindow::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(MyPopWindow);

    switch (event->type()) {
        case QEvent::MouseButtonPress: {
            QMouseEvent *mouseEvent;
            if ((mouseEvent = static_cast<QMouseEvent *>(event))) {
                // check canClose
                // auto close location
                if (!d->m_widget->geometry().contains(mouseEvent->pos())) {
					hideDialog();
				}
            }
            break;
        }

        default:
            break;
    }
    return MyOverlayWidget::eventFilter(obj, event);
}

