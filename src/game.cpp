/* src/game.cpp
 * created tue may 14 2024
 * by catroidvania
 */

#include "game.hpp"


Game::Game() {
    this->held = Piece(NOPIECE);
    this->current = Piece(NOPIECE);
    this->queue = {Piece(), Piece(), Piece(), Piece(), Piece(), Piece()};
}


void Game::nextQueuePiece() {
    this->current = Piece();
}
