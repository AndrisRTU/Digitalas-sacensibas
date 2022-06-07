#ifndef INGAMEPLAYER_H
#define INGAMEPLAYER_H

#include "GameEnums.h"
#include "IIngamePlayer.h"
#include "GameEngine.h"
#include "IngameAI.h"

class IngamePlayer : public IIngamePlayer {
private:
    Player player;
public:
    IngamePlayer(Player player);
    virtual Player getPlayer() const override;
};

class HumanPlayer : public IngamePlayer {
public:
    HumanPlayer();
    virtual void makeMove() override;
    virtual void stopCalculatingMove() override;
};

class AIPlayer : public IngamePlayer {
private:
    std::unique_ptr<IngameAI> AI;
    std::unique_ptr<QThread> thread;
public:
    AIPlayer(GameEngine& engine, std::unique_ptr<IngameAI> AI);
    virtual void makeMove() override;
    virtual void stopCalculatingMove() override;
};

#endif // INGAMEPLAYER_H
