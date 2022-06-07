#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <memory>
#include "IIngamePlayer.h"
#include "GameEngine.h"

class PlayerController {
private:
    std::unique_ptr<IIngamePlayer> firstPlayer;
    std::unique_ptr<IIngamePlayer> secondPlayer;
    GameTurn currentPlayer;
    const GameScene& scene;
    GameEngine* engine;
public:
    PlayerController(const GameScene& scene);
    void setPlayers(Player firstPlayer, uint8_t firstPlayerDifficulty, Player secondPlayer, uint8_t secondPlayerDifficulty);
    void moveIsMade();
    IIngamePlayer& getCurrentPlayer();
    const IIngamePlayer& getCurrentPlayer() const;
    const IIngamePlayer& getfirstPlayer() const;
    const IIngamePlayer& getsecondPlayer() const;
    void setEngine(GameEngine* engine);
    void setFirstTurn();
    bool canMakeMove();
    void abort();
};

#endif // PLAYERCONTROLLER_H
