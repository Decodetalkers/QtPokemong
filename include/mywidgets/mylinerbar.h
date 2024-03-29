#pragma once

#include <QWidget>

class MyLinerBarPrivate;

class MyLinerBar : public QWidget
{
    Q_OBJECT
public:
    MyLinerBar(QWidget *parent = nullptr);
    ~MyLinerBar();
#ifdef TEST
    // only can use when is defined as test
    qreal life() const;
#endif
public slots:
    void damage(qreal);
    void rebase();

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MyLinerBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyLinerBar)
    Q_DECLARE_PRIVATE(MyLinerBar)
};
