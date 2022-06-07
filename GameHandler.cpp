#include "GameHandler.h"
#include "Server.h"
#include "Client.h"
#include "RandomGenerator.h"
#include <QDateTime>

GameHandler::GameHandler() {
    scene = std::make_unique<GameScene>();
    playerController = std::make_unique<PlayerController>(*scene);
    window = std::make_unique<MainWindow>();
    window->setGameHandler(this);
    scoreArea = &window->getGameScoreArea();
    scoreArea->setGameScene(scene.get());
    gameArea = &window->getVisualGameArea();
    gameArea->setGameScene(scene.get());
    engine = std::make_unique<GameEngine>(*scene);
    playerController->setEngine(engine.get());
    window->show();
}

void GameHandler::startGame(NewGameState state, uint8_t size, Player firstPlayer, uint8_t firstPlayerDifficulty, Player secondPlayer, uint8_t secondPlayerDifficulty) {
    scene->startNewGame(state, size);
    engine->setStatsListener(gameController.get());
    gameController->setGameEngine(engine.get());
    gameController->setWindow(window.get());
    gameArea->setPositionReceiver(gameController.get());
    playerController->setPlayers(firstPlayer, firstPlayerDifficulty, secondPlayer, secondPlayerDifficulty);
    gameController->startNewGame();
}

void GameHandler::startOnlineGame() {
    auto generator = RandomGenerator::getInstance();
    uint64_t time = QDateTime::currentSecsSinceEpoch();
    generator->setSeed(time);
    onlineComponent->receiveEvent(OnlineGameEvent::setSeed, QString::number(time));
    startNewGame();
    onlineComponent->receiveEvent(OnlineGameEvent::start);
}

PlayerController& GameHandler::getPlayerController() {
    return *playerController;
}

VisualGameArea& GameHandler::getGameArea() {
    return *gameArea;
}

void GameHandler::startNewGame(NewGameState state, uint8_t size, Player firstPlayer, uint8_t firstPlayerDifficulty, Player secondPlayer, uint8_t secondPlayerDifficulty) {
    gameController = std::make_unique<GameController>(*playerController, *scene, *gameArea, *scoreArea);
    scoreArea->setPlayers(firstPlayer, secondPlayer);
    startGame(state, size, firstPlayer, firstPlayerDifficulty, secondPlayer, secondPlayerDifficulty);
}

void GameHandler::startNewGame() {
    if (window->getFirstPlayer() == onlineComponent->getPlayerName()) {
        scoreArea->setPlayers(onlineComponent->getPlayerName(), onlineComponent->getOpponentName());
        onlineComponent->setFirstTurn(GameTurn::FirstPlayer);
    }
    else {
        scoreArea->setPlayers(onlineComponent->getOpponentName(), onlineComponent->getPlayerName());
        onlineComponent->setFirstTurn(GameTurn::SecondPlayer);
    }
    NewGameState state = window->getFirstPlayerTurn();
    uint8_t size = window->getBoardSize();
    startGame(state, size, Player::Player, 0, Player::Player, 0);
}

void GameHandler::stopGame() {
    playerController->abort();
}

const GameScene& GameHandler::getScene() const {
    return *scene;
}

void GameHandler::onlineGame(const QString& host, uint16_t port, const QString& name, bool isServer) {
    if (isServer) {
        onlineComponent = std::make_unique<Server>(port, *this, name);
    }
    else {
        onlineComponent = std::make_unique<Client>(host, port, *this, name);
    }
    onlineComponent->setWindow(window.get());
    std::unique_ptr<ServerGameController> controller = std::make_unique<ServerGameController>(*playerController, *scene, *gameArea, *scoreArea, *onlineComponent);
    onlineComponent->setPositionReceiver(controller.get());
    window->setOnlineReceiver(onlineComponent.get());
    gameController.reset();
    gameController = std::move(controller);
    engine->setStatsListener(gameController.get());
    gameController->setGameEngine(engine.get());
    gameController->setWindow(window.get());
    gameArea->setPositionReceiver(gameController.get());
}

void GameHandler::hostGame(int port, const QString& name) {
    onlineGame("", port, name, true);
}

void GameHandler::joinGame(const QString& host, uint16_t port, const QString& name) {
    onlineGame(host, port, name, false);
}

void GameHandler::lobbyLeft() {
    onlineComponent.reset();
    gameController.reset();
}
