#include "PlayerController.h"
#include "ingameplayer.h"

PlayerController::PlayerController(const GameScene& scene) :
    scene(scene) {

}

void PlayerController::setPlayers(Player firstPlayer, uint8_t firstPlayerDifficulty, Player secondPlayer, uint8_t secondPlayerDifficulty) {
    if (firstPlayer == Player::AI) {
        this->firstPlayer = std::make_unique<AIPlayer>(*engine, std::make_unique<IngameAI>(firstPlayerDifficulty, scene));
    }
    else {
        this->firstPlayer = std::make_unique<HumanPlayer>();
    }
    if (secondPlayer == Player::AI) {
        this->secondPlayer = std::make_unique<AIPlayer>(*engine, std::make_unique<IngameAI>(secondPlayerDifficulty, scene));
    }
    else {
        this->secondPlayer = std::make_unique<HumanPlayer>();
    }
}

void PlayerController::moveIsMade() {
    if (currentPlayer == GameTurn::FirstPlayer) {
        currentPlayer = GameTurn::SecondPlayer;
    }
    else {
        currentPlayer = GameTurn::FirstPlayer;
    }
}

IIngamePlayer& PlayerController::getCurrentPlayer() {
    if (currentPlayer == GameTurn::FirstPlayer) {
        return *firstPlayer;
    }
    return *secondPlayer;
}

const IIngamePlayer& PlayerController::getfirstPlayer() const {
    return *firstPlayer;
}

const IIngamePlayer& PlayerController::getsecondPlayer() const {
    return *secondPlayer;
}

const IIngamePlayer& PlayerController::getCurrentPlayer() const {
    if (currentPlayer == GameTurn::FirstPlayer) {
        return *firstPlayer;
    }
    return *secondPlayer;
}

void PlayerController::setEngine(GameEngine* engine) {
    this->engine = engine;
}

void PlayerController::setFirstTurn() {
    currentPlayer = scene.getGameCondition().getTurn();
}

bool PlayerController::canMakeMove() {
    return getCurrentPlayer().getPlayer() != Player::AI;
}

void PlayerController::abort() {
    getCurrentPlayer().stopCalculatingMove();
}
