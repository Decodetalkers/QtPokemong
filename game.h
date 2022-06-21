#ifndef GAME_H
#define GAME_H

#include <QHBoxLayout>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QWidget>

class Player : public QWidget
{
    Q_OBJECT
public:
    Player(QWidget *parent = nullptr);

private:
    QLabel *player;
    void download(const QUrl url);
    int hps = 100;
    // QHBoxLayout *panel;
    // QHBoxLayout *themap;
    // QNetworkAccessManager qnam;
};

class Enermy : public QWidget
{
    Q_OBJECT
public:
    Enermy(QWidget *parent = nullptr);

private:
    QLabel *enermy;
    void loading();
    int hps = 100;
};
#endif  // !GAME_H
