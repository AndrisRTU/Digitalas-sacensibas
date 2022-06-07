#ifndef IGAMESTATSLISTENER_H
#define IGAMESTATSLISTENER_H
#include <cstdint>
#include <utility>

class IGameStatsListener {
public:
    virtual void cellPicked(int score, std::pair<uint8_t, uint8_t> position) = 0;
    virtual void nextMove() = 0;
    virtual void gameEnded() = 0;
};

#endif // IGAMESTATSLISTENER_H
