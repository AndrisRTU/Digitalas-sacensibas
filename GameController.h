#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "GameScene.h"
#include "IGameStatsListener.h"
#include "GameEngine.h"
#include "VisualGameArea.h"
#include "GameScoreArea.h"
#include "PlayerController.h"
#include "IMainWindow.h"
#include <QTimer>

class BaseGameController : public IGameStatsListener, public IGamePositionReceiver {
protected:
    PlayerController& playerController;
    GameScene& scene;
    VisualGameArea& gameArea;
    GameScoreArea& scoreArea;
    GameEngine* engine;
    IMainWindow* window;
public:
    BaseGameController(PlayerController& playerController, GameScene& scene, VisualGameArea& gameArea, GameScoreArea& scoreAre);
    virtual ~BaseGameController() = default;
    virtual void cellPicked(int score, std::pair<uint8_t, uint8_t> position) override;
    virtual void nextMove() override;
    virtual void gameEnded() override;
    virtual void startNewGame();
    void setGameEngine(GameEngine* engine);
    void setWindow(IMainWindow* window);
    virtual void receivePosition(std::pair<uint8_t, uint8_t> position) override;
};

class GameController : public BaseGameController {
public:
    GameController(PlayerController& playerController, GameScene& scene, VisualGameArea& gameArea, GameScoreArea& scoreAre);
    virtual void startNewGame() override;
};

class ServerGameController : public BaseGameController, public IGameOnlineController {
private:
    int timeToMove;
    IGameOnlinePositionReceiver& receiver;
    std::unique_ptr<QTimer> timer;
public:
    ServerGameController(PlayerController& playerController, GameScene& scene, VisualGameArea& gameArea, GameScoreArea& scoreArea, IGameOnlinePositionReceiver& receiver);
    virtual ~ServerGameController() = default;
    virtual void startNewGame() override;
    virtual void receivePosition(std::pair<uint8_t, uint8_t> position) override;
    virtual void receiveOnlinePosition(std::pair<uint8_t, uint8_t> position) override;
};

#endif // GAMECONTROLLER_H
