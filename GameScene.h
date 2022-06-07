#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Board.h"
#include "GameCondition.h"
#include "IGameScene.h"
#include <memory>

class GameScene : public IGameScene {
private:
    long long FirstPlayerWins;
    long long SecondPlayerWins;
    std::unique_ptr<Board> board;
    std::unique_ptr<GameCondition> condition;
public:
    GameScene();
    long long getFirstPlayerWins() const;
    long long getSecondPlayerWins() const;
    void gameEnded();
    virtual void startNewGame(NewGameState state, uint8_t size) override;
    IBoard& getBoard();
    const IBoard& getBoard() const;
    const IGameConditionMembers& getGameConditionMembers() const;
    IGameConditionChanger& getGameConditionChanger();
    const GameCondition& getGameCondition() const;
    void positionChanged(int score, std::pair<uint8_t, uint8_t> position);
};

#endif // GAMESCENE_H
