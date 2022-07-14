#pragma once
#include "myprogress.h"
#include <QObject>
class MyProgressDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    MyProgressDelegate(MyProgress *parent);
    ~MyProgressDelegate();
    inline void setOffset(qreal offset);
    inline qreal offset() const;

private:
    Q_DISABLE_COPY(MyProgressDelegate);

    MyProgress *const m_progress;
    qreal m_offset;
};
inline void MyProgressDelegate::setOffset(qreal offset)
{
    m_offset = offset;
    m_progress->update();
}

inline qreal MyProgressDelegate::offset() const
{
    return m_offset;
}
