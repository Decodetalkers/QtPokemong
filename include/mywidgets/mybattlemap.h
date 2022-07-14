#pragma once
#include <QWidget>
class MyBattleMapPrivate;

class MyBattleMap : public QWidget
{
    Q_OBJECT
public:
    MyBattleMap(QWidget *parent = nullptr);
    ~MyBattleMap();

public slots:
    void myAttack();
    void enermyAttack();

protected:
    //bool event(QEvent *event) override;
    //bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MyBattleMapPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyBattleMap)
    Q_DECLARE_PRIVATE(MyBattleMap)
};
