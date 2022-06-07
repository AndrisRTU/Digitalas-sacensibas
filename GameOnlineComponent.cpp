#include "GameOnlineComponent.h"
#include <QDateTime>

GameOnlineComponent::GameOnlineComponent(GameHandler& handler, const QString& playerName) :
    handler(handler),
    nextBlockSize(0),
    playerName(playerName),
    socket(nullptr) {

}

void GameOnlineComponent::setEventActionsMap() {
    eventActionsMap[OnlineGameEvent::setPosition] = [&](const QString& str) {
        QStringList position = str.split(" ");
        receiver->receiveOnlinePosition({uint8_t(position[0].toInt()), uint8_t(position[1].toInt())});
    };
    eventActionsMap[OnlineGameEvent::wroteToChat] = [&](const QString& str) {
        const QString message = "[" + QDateTime::currentDateTime().time().toString() + QString("] ") + opponentName + QString(": ") + str;
        window->eventHappened(OnlineGameEvent::wroteToChat, message);
    };
    eventActionsMap[OnlineGameEvent::returnedToLobby] = [&](const QString& str) {
        window->setMessageToInformativeLabel(opponentName + QString(" has returned to lobby"));
    };
}

void GameOnlineComponent::readForData() {
    QDataStream in(socket);
    while (true) {
        if (!nextBlockSize) {
            if (socket->bytesAvailable() < sizeof(uint16_t)) {
                break;
            }
            in >> nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize) {
            break;
        }
        OnlineGameEvent event;
        in >> event;
        QString str;
        in >> str;
        if (eventActionsMap[event]) {
            eventActionsMap[event](str);
        }
        nextBlockSize = 0;
    }
}

void GameOnlineComponent::sendData(QTcpSocket* socket, OnlineGameEvent event, const QString& str) {
    if (!socket) {
        return;
    }
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    out << uint16_t(0) << event << str;
    out.device()->seek(0);
    out << uint16_t(arrBlock.size() - sizeof(uint16_t));
    socket->write(arrBlock);
}

void GameOnlineComponent::receivePosition(std::pair<uint8_t, uint8_t> position) {
    QString message = QString::number(position.first) + QString(" ") + QString::number(position.second);
    sendData(socket, OnlineGameEvent::setPosition, message);
}

GameTurn GameOnlineComponent::getPlayer() {
    return player;
}

void GameOnlineComponent::setPositionReceiver(IGameOnlineController* receiver) {
    this->receiver = receiver;
}

void GameOnlineComponent::setWindow(IMainWindow* window) {
    this->window = window;
}

void GameOnlineComponent::setFirstTurn(GameTurn turn) {
    this->player = turn;
}

void GameOnlineComponent::receiveEvent(OnlineGameEvent event, const QString& item) {
    sendData(socket, event, item);
}

QString GameOnlineComponent::getPlayerName() {
    return playerName;
}

QString GameOnlineComponent::getOpponentName() {
    return opponentName;
}
