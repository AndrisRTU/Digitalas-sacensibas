#ifndef IGAMEONLINECOMPONENT_H
#define IGAMEONLINECOMPONENT_H
#include "GameEnums.h"
#include "IGamePositionReceiver.h"

class IGameOnlineComponent : public IGameOnlinePositionReceiver, public IOnlineEventReceiver {
public:
    virtual ~IGameOnlineComponent() {};
public:
    virtual void setPositionReceiver(IGameOnlineController* receiver) = 0;
    virtual void setWindow(IMainWindow* window) = 0;
    virtual void setFirstTurn(GameTurn turn) = 0;
    virtual QString getPlayerName() = 0;
    virtual QString getOpponentName() = 0;
};

#endif // IGAMEONLINECOMPONENT_H
