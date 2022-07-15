#pragma once

#include <QtWidgets>

class MyLinerBar;
class MyLinerBarLife;
class MyLinerBarStateMachine;
class MyLinerBarPrivate
{
    Q_DISABLE_COPY(MyLinerBarPrivate)
    Q_DECLARE_PUBLIC(MyLinerBar)
public:
    MyLinerBarPrivate(MyLinerBar *q);
    ~MyLinerBarPrivate();

    void init();

    MyLinerBar *const q_ptr;
    MyLinerBarLife *life;
    MyLinerBarStateMachine *statemachine;
};
