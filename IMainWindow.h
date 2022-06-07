#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H
#include <QString>
#include "OnlineGameEvent.h"
#include "GameEnums.h"

class IMainWindow {
public:
    virtual void eventHappened(OnlineGameEvent event, const QString& string) = 0;
    virtual NewGameState getFirstPlayerTurn() = 0;
    virtual QString getFirstPlayer() = 0;
    virtual uint8_t getBoardSize() = 0;
    virtual int getTimer() = 0;
    virtual void addPlayersToCombobox(const QString& str) = 0;
    virtual void removePlayersFromCombobox(const QString& str) = 0;
    virtual void lobbyJoined() = 0;
    virtual void goToGameAction() = 0;
    virtual void goToLobbyPage() = 0;
    virtual void setMessageToInformativeLabel(const QString& str) = 0;
    virtual void clientConnected() = 0;
};

#endif // IMAINWINDOW_H
