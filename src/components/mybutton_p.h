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
    MybuttonToggle *toggle;
    MybuttonToggleTrack *toggletrack;
    QState *offState;
    QState *onState;
    QStateMachine *stateMachine;
};
