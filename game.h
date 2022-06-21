#ifndef GAME_H
#define GAME_H

#include <QLabel>
#include <QNetworkAccessManager>
#include <QWidget>
#include <QHBoxLayout>

class Player : public QWidget {
  Q_OBJECT
public:
  Player(QWidget *parent = nullptr);


private:
  QLabel *player;
  void download(const QUrl url);
	//QHBoxLayout *panel;
	//QHBoxLayout *themap;
  // QNetworkAccessManager qnam;
};

class Enermy : public QWidget {
  Q_OBJECT
public:
  Enermy(QWidget *parent = nullptr);
private:
	QLabel *enermy;
	void loading();
};
#endif // !GAME_H
