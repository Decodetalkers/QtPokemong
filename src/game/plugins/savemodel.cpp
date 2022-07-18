#include "savemodel.h"
#include <QDebug>
#include <QGSettings/QGSettings>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtWidgets>

GSettingSaver::GSettingSaver(QWidget *parent, QGSettings *gsettings)
    : QWidget(parent)
    , m_gsettings(gsettings)
{
}
GSettingSaver::~GSettingSaver() {}

QWidget *PluginSaveModel::gamepanel(QSharedPointer<PokeMonModel> model)
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

    if (QGSettings::isSchemaInstalled("apps.eightplus.pokemongame")) {
        QGSettings *gsettings = new QGSettings("apps.eightplus.pokemongame");
        GSettingSaver *mainwidget = new GSettingSaver(nullptr, gsettings);

        QPushButton *button = new QPushButton("Save");
        connect(button, &QPushButton::clicked, mainwidget, [=] {
            qDebug() << "Saved";
            qDebug() << model->get_names();
			QStringList list = model->get_names();
            mainwidget->m_gsettings->set("ids", QVariant::fromValue(list));
            mainwidget->m_gsettings->set("names", QVariant::fromValue(model->get_names()));
            mainwidget->m_gsettings->set("weather", true);
        });
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(table);
        layout->addWidget(button);

        mainwidget->setLayout(layout);

        return mainwidget;
    } else {
        return table;
    }
}

QString PluginSaveModel::pluginname() const
{
    return "savemodel";
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
