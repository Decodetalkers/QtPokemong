#ifndef POKEMONGMAP_H
#define POKEMONGMAP_H
#include <QPaintEvent>
#include <QWidget>
#include <QRandomGenerator>
class PokemonMap : public QWidget
{
    Q_OBJECT
public:
    PokemonMap(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
signals:
	void meetenermy();
private:
	QRandomGenerator *qrand;
    QPoint enermys[6] = {
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
    };
	QPoint playerposition = {0,0};
};

#endif  // !POKEMONGMAP_H
