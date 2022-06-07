#include "GameScene.h"

GameScene::GameScene() :
    board(std::make_unique<Board>()),
    condition(std::make_unique<GameCondition>()),
    FirstPlayerWins(0),
    SecondPlayerWins(0) {

}

long long GameScene::getFirstPlayerWins() const {
    return FirstPlayerWins;
}

long long GameScene::getSecondPlayerWins() const {
    return SecondPlayerWins;
}

void GameScene::gameEnded() {
    if (condition->getFirstPlayerScore() > condition->getSecondPlayerScore()) {
        FirstPlayerWins++;
    }
    if (condition->getSecondPlayerScore() > condition->getFirstPlayerScore()) {
        SecondPlayerWins++;
    }
    condition->gameEnded();
}

void GameScene::startNewGame(NewGameState state, uint8_t size) {
    board->newGame(size);
    condition->startNewGame(state, size);
}

IBoard& GameScene::getBoard() {
    return *board;
}

const IBoard& GameScene::getBoard() const {
    return *board;
}

const IGameConditionMembers& GameScene::getGameConditionMembers() const {
    return *condition;
}

IGameConditionChanger& GameScene::getGameConditionChanger() {
    return *condition;
}

const GameCondition& GameScene::getGameCondition() const {
    return *condition;
}
