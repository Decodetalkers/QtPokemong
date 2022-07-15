#pragma once

#include <QWidget>

class MyOverlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyOverlayWidget(QWidget *parent = 0);
    ~MyOverlayWidget();

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

    virtual QRect overlayGeometry() const;

private:
    Q_DISABLE_COPY(MyOverlayWidget)
};
