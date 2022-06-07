#include "GameEngine.h"

GameEngine::GameEngine(GameScene& scene) :
    scene(scene) {

}

bool GameEngine::checkForMoves() {
    const std::vector<std::vector<NumberCell>>& cells = scene.getBoard().getBoard();
    if (scene.getGameConditionMembers().getMovement() == Movement::Horizontal) {
        int8_t x = scene.getGameConditionMembers().getPosition().first;
        for (int i = 0; i < cells.size(); i++) {
            if (!cells[x][i].isSelected()) {
                return true;
            }
        }
    }
    else {
        int8_t y = scene.getGameConditionMembers().getPosition().second;
        for (int i = 0; i < cells.size(); i++) {
            if (!cells[i][y].isSelected()) {
                return true;
            }
        }
    }
    return false;
}

void GameEngine::cellSelected(Position position) {
    const int8_t x = position.first;
    const int8_t y = position.second;
    std::vector<std::vector<NumberCell>>& cells = scene.getBoard().getBoard();
    if (cells[x][y].isSelected()) {
        return;
    }

    statsListener->cellPicked(cells[x][y].pick(), position);

    if (checkForMoves()) {
        statsListener->nextMove();
    }
    else {
        statsListener->gameEnded();
    }
}

void GameEngine::setStatsListener(IGameStatsListener* statsListener) {
    this->statsListener = statsListener;
}
