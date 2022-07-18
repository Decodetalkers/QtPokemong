#pragma once

#include <QAbstractTableModel>
#include <QDirIterator>
#include <QStyledItemDelegate>
class PokemongIcon;
class PokeMonModel;
class PokemonTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    ~PokemonTableDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


