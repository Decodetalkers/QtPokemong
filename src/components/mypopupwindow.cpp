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

    dialogWindow = new MyPopWindowDialog(q);
    proxyStack = new QStackedLayout;
    stateMachine = new QStateMachine(q);
    proxy = new MyPopWindowProxy(dialogWindow, proxyStack, q);

    QVBoxLayout *layout = new QVBoxLayout;
    q->setLayout(layout);

    widget = new QWidget;
    widget->setLayout(proxyStack);
    widget->setMinimumWidth(400);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 200));
    effect->setBlurRadius(64);
    effect->setOffset(0, 13);
    widget->setGraphicsEffect(effect);

    layout->addWidget(widget);
    layout->setAlignment(widget, Qt::AlignCenter);

    proxyStack->addWidget(dialogWindow);
    proxyStack->addWidget(proxy);
    proxyStack->setCurrentIndex(1);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QState *hiddenState = new QState;
    QState *visibleState = new QState;

    stateMachine->addState(hiddenState);
    stateMachine->addState(visibleState);
    stateMachine->setInitialState(hiddenState);

    MyStateTransition *transiton;
    transiton = new MyStateTransition(MyTransitionType::ShowDialog);
    transiton->setTargetState(visibleState);
    hiddenState->addTransition(transiton);

    transiton = new MyStateTransition(MyTransitionType::HideDialog);
    transiton->setTargetState(hiddenState);
    visibleState->addTransition(transiton);

    visibleState->assignProperty(proxy, "opacity", 1);
    visibleState->assignProperty(effect, "color", QColor(0, 0, 0, 200));
    visibleState->assignProperty(dialogWindow, "offset", 0);
    hiddenState->assignProperty(proxy, "opacity", 0);
    hiddenState->assignProperty(effect, "color", QColor(0, 0, 0, 0));
    hiddenState->assignProperty(dialogWindow, "offset", 200);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(proxy, "opacity", q);
    animation->setDuration(280);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(effect, "color", q);
    animation->setDuration(280);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(dialogWindow, "offset", q);
    animation->setDuration(280);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    stateMachine->addDefaultAnimation(animation);

    QObject::connect(visibleState, &QState::propertiesAssigned, proxy, &MyPopWindowProxy::makeOpaque);
    QObject::connect(hiddenState, &QState::propertiesAssigned, proxy, &MyPopWindowProxy::makeTransparent);

    stateMachine->start();
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
    return d->dialogWindow->layout();
}

void MyPopWindow::setWindowLayout(QLayout *layout)
{
    Q_D(MyPopWindow);

    d->dialogWindow->setLayout(layout);
}

void MyPopWindow::showDialog()
{
    Q_D(MyPopWindow);
    d->stateMachine->postEvent(new MyTransitionEvent(MyTransitionType::ShowDialog));
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    raise();
}
void MyPopWindow::hideDialog()
{
    Q_D(MyPopWindow);
    d->stateMachine->postEvent(new MyTransitionEvent(MyTransitionType::HideDialog));
    setAttribute(Qt::WA_TransparentForMouseEvents);
    d->proxyStack->setCurrentIndex(1);
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
    painter.setOpacity(d->proxy->opacity() / 2.4);
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
                if (!d->widget->geometry().contains(mouseEvent->pos())) {
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

