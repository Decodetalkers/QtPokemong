#pragma once

#include <QtPlugin>
#include <interface/plugin.h>

class pluginDemo : public QObject, public QtPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_id)
    Q_INTERFACES(QtPluginInterface)

public:
    pluginDemo(){};
    ~pluginDemo(){};
    virtual QWidget *thebutton() override;
};

