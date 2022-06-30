#ifndef POKEMONGTABLE_H
#define POKEMONGTABLE_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>
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
// TODO a Table
class PokeMonModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PokeMonModel(QObject *parent = 0);
    void populateData(const QList<PokemongIcon> &ids,const QList<QString> &names);	
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<PokemongIcon> ids;
    QList<QString> names;
};

#endif  // !POKEMONGTABLE_H
