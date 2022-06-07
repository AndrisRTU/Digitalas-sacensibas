#ifndef GAMESCOREAREA_H
#define GAMESCOREAREA_H
#include <memory>
#include "QHBoxLayout"
#include "QLabel"
#include "GameScene.h"

class GameScoreArea {
private:
    QLabel& firstPlayerScore;
    QLabel& secondPlayerScore;
    QLabel& winStatisticLabel;
    QLabel& firstPlayerTextScore;
    QLabel& secondPlayerTextScore;
    const GameScene* scene;
public:
    GameScoreArea(QLabel& firstPlayerScore, QLabel& firstPlayerTextScore, QLabel& secondPlayerScore, QLabel& secondPlayerTextScore, QLabel& winStatisticLabel);
    void update();
    void reset();
    void updateWinLabel();
    void setPlayers(const QString& firstPlayer, const QString& secondPlayer);
    void setPlayers(Player player, Player secondPlayer);
    void paintOverPlayer(GameTurn player);
    void setGameScene(const GameScene* scene);
};

#endif // GAMESCOREAREA_H
