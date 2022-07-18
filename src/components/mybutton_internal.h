#pragma once
#include <QWidget>
#include <Qt>
class MyButton;
class MybuttonToggle : public QWidget
{
    Q_OBJECT

    // shift property
    Q_PROPERTY(qreal shift WRITE setShift READ shift)
public:
    MybuttonToggle(MyButton *parent);
    ~MybuttonToggle();

    void setShift(qreal shift);
    inline qreal shift() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MybuttonToggle)

    MyButton *const m_button;
    qreal m_shift;
};

/*
 * @brief Get the shift value
 */
inline qreal MybuttonToggle::shift() const
{
    return m_shift;
}

class MybuttonToggleTrack : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)
public:
    MybuttonToggleTrack(MyButton *parent);
    ~MybuttonToggleTrack();

    void setTrackColor(const QColor &color);
    inline QColor trackColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MybuttonToggleTrack)

    MyButton *const m_button;
    QColor m_trackColor;
};

inline QColor MybuttonToggleTrack::trackColor() const
{
    return m_trackColor;
}
