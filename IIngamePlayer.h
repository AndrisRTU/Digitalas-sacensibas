#ifndef IINGAMEPLAYER_H
#define IINGAMEPLAYER_H

#include "GameEnums.h"

class IIngamePlayer {
public:
    virtual void makeMove() = 0;
    virtual void stopCalculatingMove() = 0;
    virtual Player getPlayer() const = 0;
};

#endif // IINGAMEPLAYER_H
