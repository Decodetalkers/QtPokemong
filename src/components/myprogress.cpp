#include "myprogress.h"
#include "myprogress_internal.h"
#include "myprogress_p.h"
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
MyProgressPrivate::MyProgressPrivate(MyProgress *q)
    : q_ptr(q)
{
}
MyProgressPrivate::~MyProgressPrivate() {}
void MyProgressPrivate::init()
{
    Q_Q(MyProgress);

    //q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    delegate = new MyProgressDelegate(q);

    QPropertyAnimation *animation = new QPropertyAnimation(q);

    animation->setPropertyName("offset");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1000);

    // loop forever
    animation->setLoopCount(-1);

    animation->start();
}

MyProgress::MyProgress(QWidget *parent)
    : QProgressBar(parent)
    , d_ptr(new MyProgressPrivate(this))
{
    d_func()->init();
}

MyProgress::~MyProgress() {}
void MyProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(MyProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(0, height() / 2.0 - 3, width(), 6, 3, 3);
    painter.setClipPath(path);

    painter.drawRect(0, 0, width(), height());

    brush.setColor(Qt::blue);
    painter.setBrush(brush);

    // set start point
    painter.drawRect(d->delegate->offset() * width() * 2 - width(), 0, width(), height());
}
