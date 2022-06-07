#include "NumberCell.h"
#include "RandomGenerator.h"

NumberCell::NumberCell(Position& position) :
    selected(false) {
    this->position = position;
    const auto generator = RandomGenerator::getInstance();
    number = generator->getRandomNumber(-9, 9);
}

int8_t NumberCell::pick() {
    selected = true;
    return number;
}

int8_t NumberCell::getNumber() const {
    return number;
}

std::pair<uint8_t, uint8_t> NumberCell::getPosition() const {
    return position;
}

bool NumberCell::isSelected() const {
    return selected;
}
