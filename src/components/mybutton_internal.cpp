#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <mywidgets/mybutton.h>
#include <mybutton_internal.h>
MybuttonToggle::MybuttonToggle(MyButton *parent)
    : QWidget(parent)
    , m_shift(0)
    , m_button(parent)
{
    Q_ASSERT(parent);
    parent->installEventFilter(this);
}
void MybuttonToggle::setShift(qreal shift)
{
    if (m_shift == shift) {
        return;
    }

    m_shift = shift;
    update();
}
void MybuttonToggle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(m_button->isEnabled() ? Qt::blue : Qt::white);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    int s = height() > width() ? width() / 2 : height() / 2;
    QRectF r = QRectF(m_shift * width() / 15.0 + width() / 2.0 - s / 2.0, height() / 2.0 - s / 2.0, s, s);
    painter.drawEllipse(r);
}
bool MybuttonToggle::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(m_button->rect().adjusted(8, 8, -8, -8));
    }
    return QWidget::eventFilter(obj, event);
}

MybuttonToggle::~MybuttonToggle() {}

MybuttonToggleTrack::MybuttonToggleTrack(MyButton *parent)
    : QWidget(parent)
    , m_button(parent)
{
    Q_ASSERT(parent);
    parent->installEventFilter(this);
}
MybuttonToggleTrack::~MybuttonToggleTrack() {}
void MybuttonToggleTrack::setTrackColor(const QColor &color)
{
    m_trackColor = color;
    update();
}

bool MybuttonToggleTrack::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(m_button->rect());
    }
    return QWidget::eventFilter(obj, event);
}

void MybuttonToggleTrack::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(m_trackColor);
    painter.setOpacity(0.8);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    const int h = height() / 2;
    const QRect r(0, h / 2, width(), h);
    painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h / 2.0 - 4, h / 2.0 - 4);
}
