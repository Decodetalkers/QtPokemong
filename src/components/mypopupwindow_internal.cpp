#include "mypopupwindow_internal.h"
#include <mywidgets/mypopupwindow.h>

#include <QPainter>
#include <QStackedLayout>
#include <QWidget>
MyPopWindowProxy::MyPopWindowProxy(MyPopWindowDialog *source, QStackedLayout *layout, MyPopWindow *dialog, QWidget *parent)
    : QWidget(parent)
    , m_source(source)
    , m_layout(layout)
    , m_dialog(dialog)
    , m_opacity(0)
    , m_mode(TransparencyMode::Transparent)
{
}
MyPopWindowProxy::~MyPopWindowProxy() {}

void MyPopWindowProxy::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    m_mode = TransparencyMode::SemiTransparent;
    update();
    m_dialog->update();
}

void MyPopWindowProxy::makeOpaque()
{
    m_layout->setCurrentIndex(0);
    m_opacity = 1.0;
    m_mode = TransparencyMode::Opaque;
    update();
}
void MyPopWindowProxy::makeTransparent()
{
    m_opacity = 0.0;
    m_mode = TransparencyMode::Transparent;
    update();
}
QSize MyPopWindowProxy::sizeHint() const
{
    return m_source->sizeHint();
}

bool MyPopWindowProxy::event(QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type) {
        m_source->setGeometry(geometry());
    }
    return QWidget::event(event);
}
void MyPopWindowProxy::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    if (TransparencyMode::Transparent == m_mode) {
        return;
    } else if (TransparencyMode::Opaque != m_mode) {
        painter.setOpacity(m_opacity);
    }
    QPixmap pm = m_source->grab(m_source->rect());
    painter.drawPixmap(0, 0, pm);
}

/*!
 *  @class MyPopWindowDialog
 *  @internal
 */

MyPopWindowDialog::MyPopWindowDialog(MyPopWindow *dialog, QWidget *parent)
    : QWidget(parent)
    , m_dialog(dialog)
{
}

MyPopWindowDialog::~MyPopWindowDialog() {}

void MyPopWindowDialog::setOffset(int offset)
{
    QMargins margins = m_dialog->layout()->contentsMargins();
    margins.setBottom(offset);
    m_dialog->layout()->setContentsMargins(margins);
}
int MyPopWindowDialog::offset() const
{
    return m_dialog->layout()->contentsMargins().bottom();
}
void MyPopWindowDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawRect(rect());
}

MyStateTransition::MyStateTransition(MyTransitionType type)
    : m_type(type)
{
}

bool MyStateTransition::eventTest(QEvent *event)
{
    if (event->type() != QEvent::Type(QEvent::User + 1)) {
        return false;
    }
    MyTransitionEvent *transition = static_cast<MyTransitionEvent *>(event);
    return (m_type == transition->type);
}

void MyStateTransition::onTransition(QEvent *) {}
