#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <random>

class RandomGenerator {
private:
    static RandomGenerator* instance;
    RandomGenerator();
    std::mt19937 generator;
public:
    static RandomGenerator* getInstance();
    void setSeed(uint64_t seed);
    int getRandomNumber(int min, int max);
};

#endif // RANDOMGENERATOR_H
