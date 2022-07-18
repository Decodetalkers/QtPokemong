#pragma once

#include <interface/gameinterface.h>
#include <mywidgets/models/pokemongmodel.h>

#include <QGSettings/QGSettings>
#include <QStyledItemDelegate>
#include <QtPlugin>
class PluginSaveModel : public QObject, public GamePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID GamePluginInterface_id)
    Q_INTERFACES(GamePluginInterface)

public:
    PluginSaveModel(){};
    ~PluginSaveModel(){};
    QWidget *gamepanel(QSharedPointer<PokeMonModel> model) override;
    QString pluginname() const override;

private:
    QSharedPointer<PokeMonModel> m_model;
};

class PokemonTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    ~PokemonTableDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

class GSettingSaver : public QWidget
{
    Q_OBJECT
public:
    GSettingSaver(QWidget *parent = nullptr, QGSettings *gsettings = nullptr);
    ~GSettingSaver();
    QGSettings *m_gsettings;
};
