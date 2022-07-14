#pragma once

#include <QObject>

class MyDrawer;
class MyDrawerWidget;
class MyDrawerStateMachine;

class MyDrawerPrivate
{
    Q_DISABLE_COPY(MyDrawerPrivate)
    Q_DECLARE_PUBLIC(MyDrawer)
public:
    MyDrawerPrivate(MyDrawer *q);
    ~MyDrawerPrivate();

    void init();

    bool overlay;
    MyDrawer *const q_ptr;
    MyDrawerWidget *widget;
    MyDrawerStateMachine *stateMachine;
    QWidget *window;
};
