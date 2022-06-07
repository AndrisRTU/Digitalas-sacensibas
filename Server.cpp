#include "Server.h"
#include "RandomGenerator.h"
#include <QDateTime>

Server::Server(int port, GameHandler& handler, const QString& playerName) :
    GameOnlineComponent(handler, playerName),
    server(std::make_unique<QTcpServer>(this)) {
    server->listen(QHostAddress::Any, port);
    connect(server.get(), SIGNAL(newConnection()), this, SLOT(userConnected()));
    setEventActionsMap();
}

Server::~Server() {
    server->close();
    delete socket;
}

void Server::setEventActionsMap() {
    GameOnlineComponent::setEventActionsMap();
    eventActionsMap[OnlineGameEvent::receiveOpponentName] = [&](const QString& str) {
        opponentName = str;
        window->addPlayersToCombobox(str);
        const QString message = "[" + QDateTime::currentDateTime().time().toString() + QString("] ") + opponentName + QString(" has joined to the lobby");
        window->eventHappened(OnlineGameEvent::wroteToChat, message);
    };
}

void Server::userConnected() {
    if (socket) {
        delete socket;
    }
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, this, &Server::userDisconnected);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readForData()));
    sendData(socket, OnlineGameEvent::joinedLobby);
    sendData(socket, OnlineGameEvent::receiveOpponentName, playerName);
    sendData(socket, OnlineGameEvent::firstPlayerBoxChanged, window->getFirstPlayer());
    sendData(socket, OnlineGameEvent::secondPlayerBoxChanged, window->getFirstPlayer());
    sendData(socket, OnlineGameEvent::boardSizeBoxChanged, QString::number(window->getBoardSize()));
    QString firstTurn;
    if (window->getFirstPlayerTurn() == NewGameState::Random) {
        firstTurn = "Random";
    }
    else if (window->getFirstPlayerTurn() == NewGameState::FirstPlayerTurn) {
        firstTurn = "First player";
    }
    else {
        firstTurn = "Second player";
    }
    sendData(socket, OnlineGameEvent::firstTurnBoxChanged, firstTurn);
    sendData(socket, OnlineGameEvent::timerBoxChanged, QString::number(window->getTimer()));
}

void Server::userDisconnected() {
    window->setMessageToInformativeLabel(opponentName + QString(" has disconnected"));
    QString message = "[" + QDateTime::currentDateTime().time().toString() + QString("] ") + opponentName + QString(" has left the lobby");
    window->eventHappened(OnlineGameEvent::wroteToChat, message);
    window->removePlayersFromCombobox(opponentName);
}
