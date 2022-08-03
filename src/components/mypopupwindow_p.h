#pragma once

#include <QWidget>
#include <Qt>
class MyPopWindow;
class QStateMachine;
class QStackedLayout;
class MyPopWindowProxy;
class MyPopWindowDialog;
class MyPopWindowPrivate
{
    Q_DISABLE_COPY(MyPopWindowPrivate)
    Q_DECLARE_PUBLIC(MyPopWindow)

public:
    MyPopWindowPrivate(MyPopWindow *q);
    ~MyPopWindowPrivate();

    void init();

    MyPopWindow *const q_ptr;

    QWidget *m_widget;
    MyPopWindowDialog *m_dialogWindow;
    QStackedLayout *m_proxyStack;
    QStateMachine *m_stateMachine;
    MyPopWindowProxy *m_proxy;
};
