#include "showmodel.h"

#include <QtWidgets>
QWidget *PluginShowModel::gamepanel(QSharedPointer<PokeMonModel> model)
{
    QTableView *table = new QTableView();
    table->setItemDelegate(new PokemonTableDelegate);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setDefaultSectionSize(100);
    table->verticalHeader()->setDefaultSectionSize(100);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);

    table->setModel(model.data());
    table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    table->horizontalHeader()->setStretchLastSection(true);
    return table;
}

QString PluginShowModel::pluginname() const
{
    return "PokemongMessages";
}
// const QString baseurl = "https://raw.githubusercontent.com/PokeAPI/sprites/"
//                         "master/sprites/pokemon/%1.png";
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
