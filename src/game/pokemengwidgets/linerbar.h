#pragma once

#include <QPaintEvent>
#include <QWidget>

class Linerbar : public QWidget
{
    Q_OBJECT
public:
    explicit Linerbar(QWidget *parent = nullptr);

public:
    void lifeUpdate(int newlife);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_life = 100;
};
