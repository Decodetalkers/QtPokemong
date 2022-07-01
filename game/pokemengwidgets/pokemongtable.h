#ifndef POKEMONGTABLE_H
#define POKEMONGTABLE_H

#include <QAbstractTableModel>
#include <QDirIterator>
#include <QStyledItemDelegate>
#include <optional>
class PokemonTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    ~PokemonTableDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
class PokemongIcon
{
public:
    explicit PokemongIcon(QVariant icon = QVariant(false));
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QVariant pokemonid() const { return icon; }

private:
    QVariant icon;
};

// declare to a metatype
Q_DECLARE_METATYPE(PokemongIcon)
class PokeMonModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PokeMonModel(QObject *parent = 0);
    void populateData(const QList<PokemongIcon> &ids, const QList<QString> &names);
    // return the rowcount to the table
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // return the columnCount to the table
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // handle the data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void updatedata(const PokemongIcon id, const QString name);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    // if it is editable
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    QList<PokemongIcon> ids;
    QList<QString> names;
};

#endif  // !POKEMONGTABLE_H
