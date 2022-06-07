#include "Board.h"

Board::Board(uint8_t size) :
    size(size) {
    init();
}

void Board::init() {
    board.clear();
    board.resize(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::pair<uint8_t, uint8_t> position(i, j);
            position.first = i;
            position.second = j;
            board[i].push_back(NumberCell(position));
        }
    }
}

void Board::newGame(uint8_t size) {
    this->size = size;
    init();
}

std::vector<std::vector<NumberCell>>& Board::getBoard() {
    return board;
}

const std::vector<std::vector<NumberCell>>& Board::getBoard() const {
    return board;
}

uint8_t Board::getSize() const {
    return size;
}
