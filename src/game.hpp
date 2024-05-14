/* src/game.hpp
 * created tue may 14 2024
 * by catroidvania
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "piece.hpp"


class Game : Board {
private:
    unsigned int score = 0;
    unsigned int level = 1;
    unsigned int combo = 0;
    unsigned int pieceX = 5, pieceY = 0;
    Piece held, current;
    std::vector<Piece> queue;

public:
    Game();

    void nextQueuePiece();

    inline unsigned int getScore() { return score; }
    inline unsigned int getLevel() { return level; }
    inline unsigned int getCombo() { return combo; }
    inline unsigned int getCurrentPieceX() { return pieceX; }
    inline unsigned int getCurrentPieceY() { return pieceY; }

};

#endif
