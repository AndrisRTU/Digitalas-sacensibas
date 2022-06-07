#include <QRandomGenerator>
#include "RandomGenerator.h"
#include <QDateTime>

RandomGenerator* RandomGenerator::instance = nullptr;

RandomGenerator* RandomGenerator::getInstance() {
    if (instance == nullptr) {
        instance = new RandomGenerator();
    }
    return instance;
}

RandomGenerator::RandomGenerator() {
    uint64_t time = QDateTime::currentSecsSinceEpoch();
    setSeed(time);
}
void RandomGenerator::setSeed(uint64_t seed) {
    generator.seed(seed);
}

int RandomGenerator::getRandomNumber(int min, int max) {
    return generator() % (max - min + 1) + min;
}
