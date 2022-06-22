#ifndef POKEMONGMAP_H
#define POKEMONGMAP_H
#include <QWidget>
#include <QPaintEvent>
class PokemonMap : public QWidget {
	Q_OBJECT
public: 
	PokemonMap(QWidget *parent = nullptr);
protected: 
	void paintEvent(QPaintEvent *event) override;
};

#endif // !POKEMONGMAP_H
