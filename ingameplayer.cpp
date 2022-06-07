#include "IngamePlayer.h"

IngamePlayer::IngamePlayer(Player player) :
    player(player) {

}

Player IngamePlayer::getPlayer() const {
    return player;
}

HumanPlayer::HumanPlayer() :
    IngamePlayer(Player::Player) {

}

void HumanPlayer::makeMove() {

}

void HumanPlayer::stopCalculatingMove() {

}

AIPlayer::AIPlayer(GameEngine& engine, std::unique_ptr<IngameAI> AI) :
    thread(std::make_unique<QThread>()),
    IngamePlayer(Player::AI),
    AI(std::move(AI)) {
    this->AI->moveToThread(thread.get());
    QObject::connect(thread.get(),
                     &QThread::started,
                     this->AI.get(),
                     &IngameAI::calculatePosition);

    QObject::connect(this->AI.get(),
                     &IngameAI::positionCalculated,
                     thread.get(),
                     &QThread::quit);

    qRegisterMetaType<std::pair<uint8_t, uint8_t>>("Position");
    QObject::connect(this->AI.get(),
                     &IngameAI::positionCalculated,
                     &engine,
                     &GameEngine::cellSelected);
}

void AIPlayer::makeMove() {
    thread->start();
}


void AIPlayer::stopCalculatingMove() {
    AI->abort();
}
