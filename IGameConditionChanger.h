#ifndef IGAMECONDITIONCHANGER_H
#define IGAMECONDITIONCHANGER_H
#include <utility>
#include <cstdint>
#include "GameEnums.h"

class IGameConditionChanger {
public:
    virtual void scoreChanged(int number) = 0;
    virtual void gameTurnChanged() = 0;
    virtual void movementChanged() = 0;
    virtual void positionChanged(std::pair<uint8_t, uint8_t> position) = 0;
    virtual void setTurn(GameTurn turn) = 0;
    virtual void setMovement(Movement movement) = 0;
    virtual void setPosition(std::pair<uint8_t, uint8_t> position) = 0;
};

#endif // IGAMECONDITIONCHANGER_H
