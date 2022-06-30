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
    if (index.data().canConvert<PokemongIcon>()) {
        return QSize(100, 100);
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}

PokemongIcon::PokemongIcon(int id)
    : id(id)
{
}

void PokemongIcon::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    // painter->save();
    QPixmap image = QPixmap(loadinged).scaled(100, 100);
    painter->drawPixmap(option.rect.x(), option.rect.y(), image);
    // painter->restore();
}

int PokeMonModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return ids.length();
}

int PokeMonModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}
PokeMonModel::PokeMonModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}
QVariant PokeMonModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return QVariant::fromValue(ids[index.row()]);
    } else if (index.column() == 1) {
        return names[index.row()];
    }
    return QVariant();
}
QVariant PokeMonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Id");
        } else if (section == 1) {
            return QString("Name");
        }
    }
    return QVariant();
}
void PokeMonModel::populateData(const QList<PokemongIcon> &newids, const QList<QString> &newnames)
{
    ids.clear();
    ids = newids;
    names.clear();
    names = newnames;
    return;
}

// row can be insert
bool PokeMonModel::insertRows(int row, int count,const QModelIndex & parent) {
	beginInsertRows(QModelIndex(), row, row + count - 1);
	endInsertRows();
	return true;
	  
}

void PokeMonModel::updatedata(const PokemongIcon id, const QString name) {
	insertRow(0);
	auto idsnew = ids;
	auto namesnew = names;
	ids.clear();
	names.clear();
	ids << id << idsnew;
	names << name << namesnew;
	
}
