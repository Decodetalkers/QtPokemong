#include "pokemongtable.h"
#include <mywidgets/models/pokemongmodel.h>

#include <QtWidgets>
//const QString baseurl = "https://raw.githubusercontent.com/PokeAPI/sprites/"
//                        "master/sprites/pokemon/%1.png";
const QString loadinged = ":/resources/yousaki.jpg";

void PokemonTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // if is pokemong , drawPixmap
    if (index.data().canConvert<PokemongIcon>()) {
        PokemongIcon icon = qvariant_cast<PokemongIcon>(index.data());

        icon.paint(painter, option, index);

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

// set the sizeHint
QSize PokemonTableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    if (index.data().canConvert<PokemongIcon>()) {
        return QSize(100, 100);
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}

PokemonTableDelegate::~PokemonTableDelegate() {}

