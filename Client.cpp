#include "Client.h"
#include "RandomGenerator.h"
#include <QDateTime>

Client::Client(const QString& host, uint16_t port, GameHandler& handler, const QString& playerName) :
    GameOnlineComponent(handler, playerName) {
    socket = new QTcpSocket(this);
    socket->connectToHost(host, port);
    connect(socket, SIGNAL(readyRead()), SLOT(readForData()));
    setEventActionsMap();
}

Client::~Client() {
    delete socket;
}

void Client::setEventActionsMap() {
    GameOnlineComponent::setEventActionsMap();
    eventActionsMap[OnlineGameEvent::receiveOpponentName] = [&](const QString& str) {
        opponentName = str;
        window->addPlayersToCombobox(str);
        sendData(socket, OnlineGameEvent::receiveOpponentName, playerName);
    };
    eventActionsMap[OnlineGameEvent::firstPlayerBoxChanged] = [&](const QString& str) {
        window->eventHappened(OnlineGameEvent::firstPlayerBoxChanged, str);
    };
    eventActionsMap[OnlineGameEvent::secondPlayerBoxChanged] = [&](const QString& str) {
        window->eventHappened(OnlineGameEvent::secondPlayerBoxChanged, str);
    };
    eventActionsMap[OnlineGameEvent::boardSizeBoxChanged] = [&](const QString& str) {
        window->eventHappened(OnlineGameEvent::boardSizeBoxChanged, str);
    };
    eventActionsMap[OnlineGameEvent::firstTurnBoxChanged] = [&](const QString& str) {
        window->eventHappened(OnlineGameEvent::firstTurnBoxChanged, str);
    };
    eventActionsMap[OnlineGameEvent::timerBoxChanged] = [&](const QString& str) {
        window->eventHappened(OnlineGameEvent::timerBoxChanged, str);
    };
    eventActionsMap[OnlineGameEvent::setSeed] = [&](const QString& str) {
        auto generator = RandomGenerator::getInstance();
        generator->setSeed(str.toInt());
    };
    eventActionsMap[OnlineGameEvent::joinedLobby] = [&](const QString& str) {
        window->lobbyJoined();
    };
    eventActionsMap[OnlineGameEvent::start] = [&](const QString& str) {
        handler.startNewGame();
        window->clientConnected();
    };
}
