#include "GameController.h"
#include "ingameplayer.h"
#include <QDateTime>

BaseGameController::BaseGameController(PlayerController& playerController, GameScene& scene, VisualGameArea& gameArea, GameScoreArea& scoreArea) :
    playerController(playerController),
    scene(scene),
    gameArea(gameArea),
    scoreArea(scoreArea) {

}

void BaseGameController::cellPicked(int score, std::pair<uint8_t, uint8_t> position) {
    gameArea.receivePosition(position);
    scene.getGameConditionChanger().scoreChanged(score);
    gameArea.diactivateCells();
    scene.getGameConditionChanger().gameTurnChanged();
    scene.getGameConditionChanger().positionChanged(position);
    scene.getGameConditionChanger().movementChanged();
    playerController.moveIsMade();
    gameArea.update();
    scoreArea.update();
    scoreArea.paintOverPlayer(scene.getGameCondition().getTurn());
}

void BaseGameController::nextMove() {
    playerController.getCurrentPlayer().makeMove();
}

void BaseGameController::gameEnded() {
    scene.gameEnded();
    scoreArea.updateWinLabel();
}

void BaseGameController::startNewGame() {
    playerController.setFirstTurn();
    scoreArea.reset();
    gameArea.reset();
    gameArea.update();
    playerController.getCurrentPlayer().makeMove();
    scoreArea.paintOverPlayer(scene.getGameCondition().getTurn());
}

void BaseGameController::setGameEngine(GameEngine* engine) {
    this->engine = engine;
}

void BaseGameController::setWindow(IMainWindow* window) {
    this->window = window;
}

void BaseGameController::receivePosition(std::pair<uint8_t, uint8_t> position) {
    if (playerController.canMakeMove()) {
        engine->cellSelected(position);
    }
}

GameController::GameController(PlayerController& playerController, GameScene& scene, VisualGameArea& gameArea, GameScoreArea& scoreAre) :
    BaseGameController(playerController, scene, gameArea, scoreAre) {

}

void GameController::startNewGame() {
    BaseGameController::startNewGame();
}

ServerGameController::ServerGameController(PlayerController& playerController, GameScene& scene, VisualGameArea& gameArea, GameScoreArea& scoreArea, IGameOnlinePositionReceiver& receiver) :
    BaseGameController(playerController, scene, gameArea, scoreArea),
    receiver(receiver) {

}

void ServerGameController::startNewGame() {
    BaseGameController::startNewGame();
}

void ServerGameController::receivePosition(std::pair<uint8_t, uint8_t> position) {
    if (scene.getGameCondition().getTurn() == receiver.getPlayer()) {
        receiver.receivePosition(position);
        engine->cellSelected(position);
    }
}

void ServerGameController::receiveOnlinePosition(std::pair<uint8_t, uint8_t> position) {
    engine->cellSelected(position);
}
