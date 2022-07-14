#pragma once

#include <QtWidgets/QAbstractButton>
#include <QPushButton>
class MyButtonPrivate;
class MyButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);
    ~MyButton();

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    //void mousePressEvent(QMouseEvent *event) override;

    const QScopedPointer<MyButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyButton)
    Q_DECLARE_PRIVATE(MyButton)
};
