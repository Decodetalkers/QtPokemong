#ifndef LINERBAR_H
#define LINERBAR_H

#include <QWidget>
#include <QPaintEvent>

class Linerbar : public QWidget {
	Q_OBJECT
public: 
	explicit Linerbar(QWidget *parent = nullptr);
protected: 
	void paintEvent(QPaintEvent *event) override;
private:
    int life = 50;
};

#endif // !LINERBAR_H
