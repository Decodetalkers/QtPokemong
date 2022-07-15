#pragma once

#include <mywidgets/basewidgets/myoverlaywidget.h>

#include <QLayout>
#include <QWidget>
class MyPopWindowPrivate;
class MyPopWindow : public MyOverlayWidget
{
    Q_OBJECT
public:
    explicit MyPopWindow(QWidget *parent = nullptr);
    ~MyPopWindow();

    QLayout *windowLayout() const;
    void setWindowLayout(QLayout *layout);
public slots:
    void showDialog();
    void hideDialog();

protected:
    void paintEvent(QPaintEvent *event) override;
    // bool event(QEvent *event) override;
    // bool eventFilter(QObject *obj, QEvent *event) override;

    const QScopedPointer<MyPopWindowPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyPopWindow)
    Q_DECLARE_PRIVATE(MyPopWindow)
};
