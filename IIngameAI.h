#ifndef IINGAMEAI_H
#define IINGAMEAI_H
#include <cstdint>

class IIngameAI {
public:
    virtual void setDifficulty(uint8_t difficulty) = 0;
    virtual void makeMove() = 0;
};

#endif // IINGAMEAI_H
