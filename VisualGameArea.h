#ifndef GAMEAREA_H
#define GAMEAREA_H
#include <utility>
#include <memory>
#include "QGridLayout"
#include "BoardCell.h"
#include "GameScene.h"
#include "GameEngine.h"
#include "IGamePositionReceiver.h"

class VisualGameArea : public QWidget {
    Q_OBJECT
private:
    std::unique_ptr<QGridLayout> layout;
    std::vector<std::vector<BoardCell*>> cells;
    const GameScene* scene;
    IGamePositionReceiver* positionReceiver;
private slots:
    void onClick();
public:
    VisualGameArea();
    void update();
    void diactivateCells();
    void clear();
    void reset();
    void receivePosition(std::pair<uint8_t, uint8_t> position);
    void setPositionReceiver(IGamePositionReceiver* positionReceiver);
    void setGameScene(const GameScene* scene);
};

#endif // GAMEAREA_H
