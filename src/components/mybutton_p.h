#pragma once
#include <Qt>
class MyButton;
class MybuttonToggle;
class MybuttonToggleTrack;
class QState;
class QStateMachine;
class MyButtonPrivate
{
    Q_DISABLE_COPY(MyButtonPrivate)
    Q_DECLARE_PUBLIC(MyButton)
public:
    MyButtonPrivate(MyButton *q);
    ~MyButtonPrivate();

    void init();

    MyButton *const q_ptr;
    MybuttonToggle *m_toggle;
    MybuttonToggleTrack *m_toggletrack;
    QState *m_offState;
    QState *m_onState;
    QStateMachine *m_stateMachine;
};
