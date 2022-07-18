#pragma once
#include <QAbstractTableModel>
#include <QPainter>
#include <QStyleOptionViewItem>
class PokemongIcon
{
public:
    explicit PokemongIcon(QVariant icon = QVariant(false), int id = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    inline QVariant pokemonid() const { return m_icon; }
    inline int getid() const { return m_id; }

private:
    QVariant m_icon;
    int m_id;
};
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
    void updateData(const PokemongIcon id, const QString name);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    // if it is editable
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    inline QList<QString> get_names() const;

private:
    QList<PokemongIcon> m_ids;
    QList<QString> m_names;
};
QList<QString> PokeMonModel::get_names() const
{
    return m_names;
}
