#include "pokemongtable.h"
#include "pokemongmodel.h"

#include <QFutureWatcher>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QVariant>
#include <QtConcurrent>
#include <QtWidgets>
#include <optional>
const QString baseurl = "https://raw.githubusercontent.com/PokeAPI/sprites/"
                        "master/sprites/pokemon/%1.png";
const QString loadinged = ":/resources/yousaki.jpg";
// dowmload the picture
QFuture<QByteArray> download(const QUrl url)
{
    return QtConcurrent::run([=] {
        QNetworkAccessManager qam = QNetworkAccessManager();
        QNetworkRequest request(url);
        auto before = qam.get(request);
        // await , oh ,sorry , cpp does have await now ,:(;
        {
            QEventLoop loop;
            QObject::connect(before, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            loop.exec();
        }
        // it will alive in the scope
        auto newbefore = QScopedPointer(before);
        auto res = newbefore->readAll();
        if (before->error() != QNetworkReply::NoError) {
            qDebug() << "error";
        }
        QThread::sleep(1);
        return res;
    });
}

// paint the table
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

