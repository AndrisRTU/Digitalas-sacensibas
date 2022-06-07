#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include "GameOnlineComponent.h"

class Server : public GameOnlineComponent {
    Q_OBJECT
private:
    std::unique_ptr<QTcpServer> server;
    virtual void setEventActionsMap() override;
public:
    Server(int port, GameHandler& handler, const QString& playerName);
    virtual ~Server();
private slots:
    void userConnected();
    void userDisconnected();
};

#endif // SERVER_H
