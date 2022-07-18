#include <mywidgets/models/pokemongmodel.h>

const QString loadinged = ":/resources/yousaki.jpg";
PokemongIcon::PokemongIcon(QVariant icon, int id)
    : m_icon(icon)
    , m_id(id)
{
}

void PokemongIcon::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    if (!m_icon.value<bool>()) {
        QPixmap image = QPixmap(loadinged).scaled(100, 100);
        painter->drawPixmap(option.rect.x(), option.rect.y(), image);
    } else {
        auto buffer = m_icon.value<QByteArray>();
        QPixmap image;
        image.loadFromData(buffer);
        painter->drawPixmap(option.rect.x(), option.rect.y(), image);
    }
}

int PokeMonModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_ids.length();
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
        return QVariant::fromValue(m_ids[index.row()]);
    } else if (index.column() == 1) {
        return m_names[index.row()];
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
    m_ids.clear();
    m_ids = newids;
    m_names.clear();
    m_names = newnames;
    return;
}

// row can be insert
bool PokeMonModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);
    endInsertRows();
    return true;
}
// is a new pokemon is catched
void PokeMonModel::updateData(const PokemongIcon id, const QString name)
{
    auto idsnew = m_ids;
    auto namesnew = m_names;
    m_ids.clear();
    m_names.clear();
    m_ids << id << idsnew;
    m_names << name << namesnew;
    insertRow(0);
}
// set flags if is icon
Qt::ItemFlags PokeMonModel::flags(const QModelIndex &index) const
{
    if (index.data().canConvert<PokemongIcon>()) {
        return Qt::NoItemFlags;
    } else {
        return (Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
    }
}
// here to reset the names
bool PokeMonModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)
    // qDebug() << index.column();
    // qDebug() << index.row();
    if (index.column() == 1) {
        m_names[index.row()] = value.value<QString>();
        return true;
    }
    return false;
}
QList<int> PokeMonModel::get_ids() const
{
    QList<int> output;
    for (auto const id : m_ids) {
        output.push_back(id.getid());
    }
    return output;
}
