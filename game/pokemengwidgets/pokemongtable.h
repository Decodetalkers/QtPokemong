#ifndef POKEMONGTABLE_H
#define POKEMONGTABLE_H

#include <QStyledItemDelegate>
#include <QAbstractTableModel>
class PokemonTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


class PokemongIcon
{
public:
	explicit PokemongIcon(int id = 1);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    int pokemonid() const { return id; }

private:
    int id;
};

Q_DECLARE_METATYPE(PokemongIcon)
#endif  // !POKEMONGTABLE_H
