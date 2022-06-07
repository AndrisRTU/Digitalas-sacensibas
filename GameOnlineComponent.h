#ifndef ONLINECOMPONENT_H
#define ONLINECOMPONENT_H
#include <QTcpSocket>
#include <unordered_map>
#include "GameHandler.h"
#include "OnlineGameEvent.h"
#include "IGameOnlineComponent.h"

class GameOnlineComponent : public QObject, public IGameOnlineComponent {
    Q_OBJECT
protected:
    QString playerName;
    QString opponentName;
    GameTurn player;
    QTcpSocket* socket;
    uint16_t nextBlockSize;
    GameHandler& handler;
    IGameOnlineController* receiver;
    IMainWindow* window;
    std::unordered_map<OnlineGameEvent, std::function<void(const QString&)>> eventActionsMap;
    void sendData(QTcpSocket* socket, OnlineGameEvent event, const QString& str = "");
    virtual void setEventActionsMap();
protected slots:
    void readForData();
public:
    GameOnlineComponent(GameHandler& handler, const QString& playerName);
    virtual ~GameOnlineComponent() = default;
    virtual void receivePosition(std::pair<uint8_t, uint8_t> position) override;
    virtual GameTurn getPlayer() override;
    virtual void setPositionReceiver(IGameOnlineController* receiver) override;
    virtual void setWindow(IMainWindow* window) override;
    virtual void setFirstTurn(GameTurn turn) override;
    virtual void receiveEvent(OnlineGameEvent event, const QString& item = "") override;
    virtual QString getPlayerName() override;
    virtual QString getOpponentName() override;
};

#endif // ONLINECOMPONENT_H
