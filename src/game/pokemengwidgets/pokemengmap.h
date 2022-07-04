#ifndef POKEMONGMAP_H
#define POKEMONGMAP_H
#include <QPaintEvent>
#include <QRandomGenerator>
#include <QWidget>
class PokemonMap : public QWidget
{
    Q_OBJECT
public:
    PokemonMap(QWidget *parent = nullptr);

public slots:
	void drawmessageupdate(QString weather);
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
signals:
    void meetenermy();

private:
    QRandomGenerator *qrand;
    QPoint enermys[16] = {
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
    };
    QPoint playerposition = {0, 0};
    bool hasmessage = false;
    QString message = "";
};

#endif  // !POKEMONGMAP_H
