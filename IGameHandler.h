#ifndef IGAMEHANDLER_H
#define IGAMEHANDLER_H
#include <cstdint>
#include <QString>
#include "GameEnums.h"
#include "GameScene.h"

class IGameHandler {
public:
    virtual void startNewGame(NewGameState state, uint8_t size, Player firstPlayer, uint8_t firstPlayerDifficulty, Player secondPlayer, uint8_t secondPlayerDifficulty) = 0;
    virtual void startNewGame() = 0;
    virtual void startOnlineGame() = 0;
    virtual void stopGame() = 0;
    virtual const GameScene& getScene() const = 0;
    virtual void hostGame(int port, const QString& name) = 0;
    virtual void joinGame(const QString& host, uint16_t port, const QString& name) = 0;
    virtual void lobbyLeft() = 0;
};
#endif // IGAMEHANDLER_H
