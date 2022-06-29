#include "pokemongtable.h"
#include <QtWidgets>

const QString loadinged = ":/resources/yousaki.jpg";
void PokemonTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data().canConvert<PokemongIcon>()) {
        PokemongIcon icon = qvariant_cast<PokemongIcon>(index.data());
        icon.paint(painter, option, index);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
// TODO use the value in index
QSize PokemonTableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    return QSize(40, 40);
}

PokemongIcon::PokemongIcon(int id)
    : id(id)
{
}

void PokemongIcon::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(option)
    //painter->save();
    QPixmap image = QPixmap(loadinged).scaled(40, 40);
    painter->drawPixmap(option.rect.x(), option.rect.y(), image);
    //painter->restore();
}
