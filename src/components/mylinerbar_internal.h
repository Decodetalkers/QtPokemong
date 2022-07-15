#pragma once

#include <QStateMachine>
#include <QWidget>
class MyLinerBar;
class MyLinerBarLife;

class MyLinerBarStateMachine : public QStateMachine
{
    Q_OBJECT
public:
    explicit MyLinerBarStateMachine(MyLinerBar *parent, MyLinerBarLife *mylife);
    ~MyLinerBarStateMachine();
    void updatePropertyAssignment();
	inline qreal getlife() const;
public slots:
	void updateAfterAssignment(qreal);
	void rebase();
private:
    Q_DISABLE_COPY(MyLinerBarStateMachine)

	qreal life;
    QState *const m_beforeState;
    QState *const m_afterState;
    MyLinerBarLife *const m_life;
    MyLinerBar *const m_bar;
signals:
    void attack();
};
inline qreal MyLinerBarStateMachine::getlife() const {
	return life;
}
class MyLinerBarLife : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal life WRITE setLife READ life)
    Q_PROPERTY(qreal deletedlife WRITE setDeletedlife READ deletedlife)
public:
    MyLinerBarLife(MyLinerBar *parent);
    ~MyLinerBarLife();

    void setDeletedlife(qreal life);
    inline qreal deletedlife() const;

    void setLife(qreal life);
    inline qreal life() const;

protected:
    bool eventFilter(QObject *obj, QEvent *evnet) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MyLinerBarLife)

    MyLinerBar *const m_linerbar;
    qreal m_life;
    qreal m_deletedlife;
};

inline qreal MyLinerBarLife::life() const
{
    return m_life;
}

inline qreal MyLinerBarLife::deletedlife() const
{
    return m_deletedlife;
}
