/* src/board.cpp
 * created fri may 3 2024
 * by catroidvania
 */

#include "board.hpp"

Board::Board() {
    this->board = std::vector<Tile>(this->width * this->height, EMPTY);
}
