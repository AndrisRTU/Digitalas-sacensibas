#ifndef BOARDGAMECELL_H
#define BOARDGAMECELL_H
#include <cstdint>
#include <utility>

class NumberCell {
private:
    int8_t number;
    using Position = std::pair<uint8_t, uint8_t>;
    Position position;
    bool selected;
public:
    NumberCell(Position& position);
    int8_t pick();
    int8_t getNumber() const;
    std::pair<uint8_t, uint8_t> getPosition() const;
    bool isSelected() const;
};

#endif // BOARDGAMECELL_H
