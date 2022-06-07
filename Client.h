#ifndef CLIENT_H
#define CLIENT_H
#include "GameOnlineComponent.h"

class Client : public GameOnlineComponent {
    Q_OBJECT
private:
    GameTurn turn;
    Movement movement;
    uint8_t x, y;
    virtual void setEventActionsMap() override;
public:
    Client(const QString& host, uint16_t port, GameHandler& handler, const QString& playerName);
    ~Client();
};

#endif // CLIENT_H
