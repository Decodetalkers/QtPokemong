#include "pokemongtable.h"
#include <QFutureWatcher>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtConcurrent>
#include <QtWidgets>
const QString baseurl = "https://raw.githubusercontent.com/PokeAPI/sprites/"
                        "master/sprites/pokemon/%1.png";
const QString loadinged = ":/resources/yousaki.jpg";
// dowmload the picture
//QFuture<QByteArray> download(const QUrl url)
//{
//    return QtConcurrent::run([=] {
//        QNetworkAccessManager qam = QNetworkAccessManager();
//        QNetworkRequest request(url);
//        auto before = qam.get(request);
//        // await , oh ,sorry , cpp does have await now ,:(;
//        {
//            QEventLoop loop;
//            QObject::connect(before, &QNetworkReply::finished, &loop, &QEventLoop::quit);
//            loop.exec();
//        }
//        auto newbefore = QScopedPointer(before);
//        auto res = newbefore->readAll();
//        if (before->error() != QNetworkReply::NoError) {
//            qDebug() << "error";
//        }
//        QThread::sleep(1);
//        return res;
//    });
//}
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
    //QFuture<QByteArray> t1 = download(QString(baseurl).arg(id));
    QPixmap image = QPixmap(loadinged).scaled(100, 100);
    painter->drawPixmap(option.rect.x(), option.rect.y(), image);
    //QFutureWatcher<QByteArray> *watcher = new QFutureWatcher<QByteArray>();
    //QObject::connect(watcher, &QFutureWatcher<QByteArray>::finished,  [watcher, painter,option] {
    //    watcher->deleteLater();
    //    auto array = watcher->result();
    //    QPixmap image;
    //    image.loadFromData(array);
	//	painter->drawPixmap(option.rect.x(), option.rect.y(), image);
	//});
	//watcher->setFuture(t1);
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
bool PokeMonModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);
    endInsertRows();
    return true;
}

void PokeMonModel::updatedata(const PokemongIcon id, const QString name)
{
    insertRow(0);
    auto idsnew = ids;
    auto namesnew = names;
    ids.clear();
    names.clear();
    ids << id << idsnew;
    names << name << namesnew;
}
