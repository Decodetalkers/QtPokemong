#pragma once

#include <basewidgets/myoverlaywidget.h>

#include <QStateMachine>

class MyDrawer;

class MyDrawerWidget;

class MyDrawerStateMachine : public QStateMachine
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    explicit MyDrawerStateMachine(MyDrawerWidget *drawer, MyDrawer *parent);
    ~MyDrawerStateMachine();

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

    inline bool isInClosedState() const;

    void updatePropertyAssignments();

signals:
    void signalOpen();
    void signalClose();

private:
    Q_DISABLE_COPY(MyDrawerStateMachine)

    MyDrawerWidget *const m_drawer;
    MyDrawer *const m_main;

    QState *const m_openingState;
    QState *const m_openedState;
    QState *const m_closingState;
    QState *const m_closedState;
    qreal m_opacity;
};

inline qreal MyDrawerStateMachine::opacity() const
{
    return m_opacity;
}

inline bool MyDrawerStateMachine::isInClosedState() const
{
    return m_closedState->active();
}

class MyDrawerWidget : public MyOverlayWidget
{
    Q_OBJECT
    Q_PROPERTY(int offset WRITE setOffset READ offset)
public:
    explicit MyDrawerWidget(QWidget *parent = nullptr);
    ~MyDrawerWidget();

    void setOffset(int offset);
    inline int offset() const;

protected:
    void paintEvent(QPaintEvent *event) override;

    QRect overlayGeometry() const override;

private:
    int m_offset;
};

inline int MyDrawerWidget::offset() const
{
    return m_offset;
}
