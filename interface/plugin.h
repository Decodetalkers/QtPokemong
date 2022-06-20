#ifndef PLUGIN_H
#define PLUGIN_H

#include <QWidget>

class QtPluginInterface {
public:
  virtual QWidget *thebutton() = 0;
};

#define PluginInterface_id "MainInterface"
Q_DECLARE_INTERFACE(QtPluginInterface, PluginInterface_id)

#endif // !PLUGIN_H
