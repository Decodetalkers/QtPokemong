#pragma once

#include <QState>
#include <QStateMachine>
#include <QWidget>

class MyBattleMap;
class MyBattleMapMime;
class MyBattleMapEnermy;
class MyBattleMapStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    explicit MyBattleMapStateMachine(MyBattleMap *battlemap, MyBattleMapMime *mypokemong, MyBattleMapEnermy *enermy);
    ~MyBattleMapStateMachine();
    void updatePropertyAssignment();

private:
    Q_DISABLE_COPY(MyBattleMapStateMachine)

    QState *const m_normalState;
    QState *const m_meattackingState;
    QState *const m_enermyattackingState;
    MyBattleMap *const m_battlemap;
    MyBattleMapMime *const m_mime;
    MyBattleMapEnermy *const m_enermy;

signals:
    void signalMimeAttack();
    void signamAnermyAttack();
};

class MyBattleMapMime : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal positionx WRITE setPositionX READ positionx)
    Q_PROPERTY(qreal positiony WRITE setPositionY READ positiony)
public:
    explicit MyBattleMapMime(MyBattleMap *parent = nullptr);
    ~MyBattleMapMime();
    void setPositionX(const qreal locationx);
    void setPositionY(const qreal locationy);
    inline qreal positionx() const;
    inline qreal positiony() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Q_DISABLE_COPY(MyBattleMapMime)

    MyBattleMap *const m_map;
    qreal m_x;
    qreal m_y;
};

inline qreal MyBattleMapMime::positionx() const
{
    return m_x;
}
inline qreal MyBattleMapMime::positiony() const
{
    return m_y;
}
class MyBattleMapEnermy : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal positionx WRITE setPositionX READ positionx)
    Q_PROPERTY(qreal positiony WRITE setPositionY READ positiony)
public:
    explicit MyBattleMapEnermy(MyBattleMap *parent = nullptr);
    ~MyBattleMapEnermy();
    void setPositionX(const qreal locationx);
    void setPositionY(const qreal locationy);
    inline qreal positionx() const;
    inline qreal positiony() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Q_DISABLE_COPY(MyBattleMapEnermy)

    MyBattleMap *const m_map;
    qreal m_x;
    qreal m_y;
};

inline qreal MyBattleMapEnermy::positionx() const
{
    return m_x;
}
inline qreal MyBattleMapEnermy::positiony() const
{
    return m_y;
}
