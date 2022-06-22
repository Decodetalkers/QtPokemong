#include "pokemengmap.h"
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
const QString grass = ":/resources/grass.jpg";
PokemonMap::PokemonMap(QWidget *parent)
    : QWidget(parent)
{
	setMinimumSize(300,300);
}

void PokemonMap::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	QPixmap image(grass);
	painter.drawPixmap(100,0,image);
	//painter.drawPixmap
}
