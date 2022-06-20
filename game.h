#ifndef GAME_H
#define GAME_H

#include <QWidget>

class Player : public QWidget {
Q_OBJECT
public:
	Player(QWidget *parent =nullptr);
};

class Enermy : public QWidget {
Q_OBJECT
public:
	Enermy(QWidget *parent =nullptr);
};
#endif // !GAME_H
