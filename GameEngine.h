#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "GameScene.h"
#include "IGameStatsListener.h"
#include <QThread>

class GameEngine : public QObject {
    Q_OBJECT
private:
    GameScene& scene;
    IGameStatsListener* statsListener;
    bool checkForMoves();
    using Position = std::pair<uint8_t, uint8_t>;
public:
    GameEngine(GameScene& scene);
    void cellSelected(Position position);
    void setStatsListener(IGameStatsListener* statsListener);
};

#endif // GAMEENGINE_H
