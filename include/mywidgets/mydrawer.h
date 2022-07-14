#pragma once

#include <basewidgets/myoverlaywidget.h>

class MyDrawerPrivate;

class MyDrawer : public MyOverlayWidget
{
    Q_OBJECT

public:
    explicit MyDrawer(QWidget *parent = nullptr);
    ~MyDrawer();
    void setDrawerLayout(QLayout *layout);
public slots:
    void openDrawer();
    void closeDrawer();
    void setOverlay(bool);

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MyDrawerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyDrawer)
    Q_DECLARE_PRIVATE(MyDrawer)
};
