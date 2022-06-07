#include "GameScoreArea.h"
#include "QVBoxLayout"

GameScoreArea::GameScoreArea(QLabel& firstPlayerScore, QLabel& firstPlayerTextScore, QLabel& secondPlayerScore, QLabel& secondPlayerTextScore, QLabel& winStatisticLabel) :
    firstPlayerScore(firstPlayerScore),
    firstPlayerTextScore(firstPlayerTextScore),
    secondPlayerScore(secondPlayerScore),
    secondPlayerTextScore(secondPlayerTextScore),
    winStatisticLabel(winStatisticLabel) {

}

void GameScoreArea::update() {
    QString strScore = QString::number(scene->getGameConditionMembers().getFirstPlayerScore());
    firstPlayerScore.setText(strScore);
    strScore = QString::number(scene->getGameConditionMembers().getSecondPlayerScore());
    secondPlayerScore.setText(strScore);
}

void GameScoreArea::reset() {
    const QString zero = QString::number(0);
    firstPlayerScore.setText(zero);
    secondPlayerScore.setText(zero);
}

void GameScoreArea::updateWinLabel() {
    const QString firstPlayerWins = QString::number(scene->getFirstPlayerWins());
    const QString secondPlayerWins = QString::number(scene->getSecondPlayerWins());
    winStatisticLabel.setText(firstPlayerWins + ":" + secondPlayerWins);
}

void GameScoreArea::setPlayers(const QString& firstPlayer, const QString& secondPlayer) {
    firstPlayerTextScore.setText(firstPlayer);
    secondPlayerTextScore.setText(secondPlayer);
}

void GameScoreArea::setPlayers(Player player, Player secondPlayer) {
    if (player == Player::Player) {
        firstPlayerTextScore.setText("Player score");
    }
    else {
        firstPlayerTextScore.setText("AI score");
    }
    if (secondPlayer == Player::Player) {
        secondPlayerTextScore.setText("Player score");
    }
    else {
        secondPlayerTextScore.setText("AI score");
    }
}

void GameScoreArea::paintOverPlayer(GameTurn player) {
    if (player == GameTurn::FirstPlayer) {
        firstPlayerTextScore.setStyleSheet("background-color: #3198FF;");
        secondPlayerTextScore.setStyleSheet("background-color: rgba(0,0,0,0%);");
    }
    else {
        firstPlayerTextScore.setStyleSheet("background-color: rgba(0,0,0,0%);");
        secondPlayerTextScore.setStyleSheet("background-color: #FF9830;");
    }
}

void GameScoreArea::setGameScene(const GameScene* scene) {
    this->scene = scene;
}
