#pragma once

#include <QWidget>
#include <QPaintEvent>

class Linerbar : public QWidget {
	Q_OBJECT
public: 
	explicit Linerbar(QWidget *parent = nullptr);
public:
    void lifeupdate(int newlife);
protected: 
	void paintEvent(QPaintEvent *event) override;
private:
    int life = 100;
};

