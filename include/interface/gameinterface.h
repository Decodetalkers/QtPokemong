#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <QAbstractTableModel>
#include <QWidget>
class PokeMonModel;
/*
 * @class GamePluginInterface
 * @brief define the interface of panel
 */
class GamePluginInterface
{
public:
    /*
     * @fn gamepanel
     * @brief return a gamepanel
     */
    virtual QWidget *gamepanel(QSharedPointer<PokeMonModel> model) = 0;
    /*
     * @fn pluginname
     * @brief return the name of plugin
     */
    virtual QString pluginname() const = 0;
};

#define GamePluginInterface_id "GAMEINTERFACE"
Q_DECLARE_INTERFACE(GamePluginInterface, GamePluginInterface_id)

#endif  // !GAME_INTERFACE_H
