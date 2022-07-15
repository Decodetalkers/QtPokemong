
#include "mydrawer_internal.h"
#include "mydrawer_p.h"
#include <QCoreApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <mywidgets/mydrawer.h>
/*!
 *  @class MyDrawerPrivate
 *  @internal
 *
 */

MyDrawerPrivate::MyDrawerPrivate(MyDrawer *q)
    : q_ptr(q)
{
}

/* !
 * @internal
 * @brief init the privite class
 */

void MyDrawerPrivate::init()
{
    Q_Q(MyDrawer);

    widget = new MyDrawerWidget;
    stateMachine = new MyDrawerStateMachine(widget, q);
    window = new QWidget;
    overlay = true;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(window);

    widget->setLayout(layout);
    widget->setFixedWidth(265);

    widget->setParent(q);

    stateMachine->start();
    QCoreApplication::processEvents();
}

MyDrawerPrivate::~MyDrawerPrivate() {}

MyDrawer::MyDrawer(QWidget *parent)
    : MyOverlayWidget(parent)
    , d_ptr(new MyDrawerPrivate(this))
{
    d_func()->init();
}

MyDrawer::~MyDrawer() {}

void MyDrawer::setDrawerLayout(QLayout *layout)
{
    Q_D(MyDrawer);

    d->window->setLayout(layout);
}

void MyDrawer::openDrawer()
{
    Q_D(MyDrawer);

    emit d->stateMachine->signalOpen();

    raise();
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setAttribute(Qt::WA_NoSystemBackground, false);
}
void MyDrawer::closeDrawer()
{
    Q_D(MyDrawer);

    emit d->stateMachine->signalClose();

    raise();
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

void MyDrawer::setOverlay(bool overlay)
{
    Q_D(MyDrawer);
    d->overlay = overlay;
}

bool MyDrawer::event(QEvent *event)
{
    Q_D(MyDrawer);

    switch (event->type()) {
        case QEvent::Move:
        case QEvent::Resize:
            if (!d->overlay)
                setMask(QRegion(d->widget->rect()));
            break;
        default:
            break;
    }
    return MyOverlayWidget::event(event);
}

// size
bool MyDrawer::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(MyDrawer);

    switch (event->type()) {
        case QEvent::MouseButtonPress: {
            QMouseEvent *mouseEvent;
            if ((mouseEvent = static_cast<QMouseEvent *>(event))) {
                // check canClose
                // auto close location
                if (!d->widget->geometry().contains(mouseEvent->pos())) {
                    closeDrawer();
                }
            }
            break;
        }
        case QEvent::Move:
        case QEvent::Resize: {
            QLayout *lw = d->widget->layout();
            if (lw && 16 != lw->contentsMargins().right()) {
                lw->setContentsMargins(0, 0, 16, 0);
            }
            break;
        }
        default:
            break;
    }
    return MyOverlayWidget::eventFilter(obj, event);
}

void MyDrawer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(MyDrawer);

    // shadow
    QPainter painter(this);
    painter.setOpacity(d->stateMachine->opacity());
    painter.fillRect(rect(), Qt::SolidPattern);
}
