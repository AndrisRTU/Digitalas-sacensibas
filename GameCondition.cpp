#include "GameCondition.h"
#include "RandomGenerator.h"

GameCondition::GameCondition() :
    firstPlayerScore(0),
    secondPlayerScore(0),
    turn(GameTurn::FirstPlayer),
    movement(Movement::Vertical),
    position({0, 0}) {

}

void GameCondition::scoreChanged(int number){
    if (turn == GameTurn::FirstPlayer) {
        firstPlayerScore += number;
    }
    else {
        secondPlayerScore += number;
    }
}

void GameCondition::gameTurnChanged(){
    if (turn == GameTurn::FirstPlayer) {
        turn = GameTurn::SecondPlayer;
    }
    else {
        turn = GameTurn::FirstPlayer;
    }
}

void GameCondition::movementChanged(){
    if (movement == Movement::Horizontal) {
        movement = Movement::Vertical;
    }
    else {
        movement = Movement::Horizontal;
    }
}

void GameCondition::positionChanged(std::pair<uint8_t,uint8_t>position) {
    this->position = position;
}

void GameCondition::gameEnded() {
    firstPlayerScore = 0;
    secondPlayerScore = 0;
}

void GameCondition::startNewGame(NewGameState state, uint8_t size) {
    const auto generator = RandomGenerator::getInstance();
    if (state == NewGameState::Random) {
        if (generator->getRandomNumber(0, 1) == 0) {
            turn = GameTurn::FirstPlayer;
        }
        else {
            turn = GameTurn::SecondPlayer;
        }
    }
    else if (state == NewGameState::FirstPlayerTurn) {
        turn = GameTurn::FirstPlayer;
    }
    else {
        turn = GameTurn::SecondPlayer;
    }
    if (generator->getRandomNumber(0, 1) == 0) {
        movement = Movement::Horizontal;
    }
    else {
        movement = Movement::Vertical;
    }
    position.first = generator->getRandomNumber(0, size - 1);
    position.second = generator->getRandomNumber(0, size - 1);
    firstPlayerScore = 0;
    secondPlayerScore = 0;
}

int GameCondition::getFirstPlayerScore() const {
    return firstPlayerScore;
}

int GameCondition::getSecondPlayerScore() const {
    return secondPlayerScore;
}

GameTurn GameCondition::getTurn() const {
    return turn;
}

Movement GameCondition::getMovement() const {
    return movement;
}

std::pair<uint8_t, uint8_t> GameCondition::getPosition() const {
    return position;
}

void GameCondition::setTurn(GameTurn turn) {
    this->turn = turn;
}

void GameCondition::setMovement(Movement movement) {
    this->movement = movement;
}

void GameCondition::setPosition(std::pair<uint8_t, uint8_t> position) {
    this->position = position;
}
