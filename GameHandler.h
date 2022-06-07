#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
#include "GameController.h"
#include "mainwindow.h"
#include "IGameHandler.h"
#include "IGameOnlineComponent.h"

class GameHandler : public IGameHandler {
private:
    std::unique_ptr<GameScene> scene;
    std::unique_ptr<GameEngine> engine;
    std::unique_ptr<BaseGameController> gameController;
    std::unique_ptr<PlayerController> playerController;
    std::unique_ptr<MainWindow> window;
    std::unique_ptr<IGameOnlineComponent> onlineComponent;
    VisualGameArea* gameArea;
    GameScoreArea* scoreArea;
    void startGame(NewGameState state, uint8_t size, Player firstPlayer, uint8_t firstPlayerDifficulty, Player secondPlayer, uint8_t secondPlayerDifficulty);
    void onlineGame(const QString& host, uint16_t port, const QString& name, bool isServer);
public:
    GameHandler();
    PlayerController& getPlayerController();
    VisualGameArea& getGameArea();
    virtual void startNewGame(NewGameState state, uint8_t size, Player firstPlayer, uint8_t firstPlayerDifficulty, Player secondPlayer, uint8_t secondPlayerDifficulty) override;
    virtual void startNewGame() override;
    virtual void startOnlineGame() override;
    virtual void stopGame() override;
    virtual const GameScene& getScene() const override;
    virtual void hostGame(int port, const QString& name) override;
    virtual void joinGame(const QString& host, uint16_t port, const QString& name) override;
    virtual void lobbyLeft() override;
};

#endif // GAMEHANDLER_H
