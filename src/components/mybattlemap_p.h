#pragma once
#include <QtWidgets>
class QStateMachine;
class QState;
class MyBattleMapMime;
class MyBattleMapEnermy;
class MyBattleMapStateMachine;
class MyBattleMap;
class MyBattleMapPrivate
{
    Q_DISABLE_COPY(MyBattleMapPrivate)
    Q_DECLARE_PUBLIC(MyBattleMap)

public:
    MyBattleMapPrivate(MyBattleMap *q);
    ~MyBattleMapPrivate();

    void init();

    MyBattleMap *const q_ptr;
    MyBattleMapMime *mime;
    MyBattleMapEnermy *enermy;
    MyBattleMapStateMachine *stateMachine;
};
