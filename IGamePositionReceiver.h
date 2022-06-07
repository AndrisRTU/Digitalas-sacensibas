#ifndef IGAMEPOSITIONRECEIVER_H
#define IGAMEPOSITIONRECEIVER_H
#include <utility>
#include <cstdint>
#include <QObject>
#include "GameEnums.h"
#include "IMainWindow.h"
#include "IOnlineEventReceiver.h"

class IGamePositionReceiver {
public slots:
    virtual void receivePosition(std::pair<uint8_t, uint8_t> position) = 0;
};

class IGameOnlineController {
public slots:
    virtual void receiveOnlinePosition(std::pair<uint8_t, uint8_t> position) = 0;
};

class IGameOnlinePositionReceiver : public IGamePositionReceiver {
public:
    virtual GameTurn getPlayer() = 0;
};


#endif // IGAMEPOSITIONRECEIVER_H
