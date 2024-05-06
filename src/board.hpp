/* src/board.hpp
 * created fri may 3 2024
 * by catroidvania
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#define TETRIS_BOARD_WIDTH 10
#define TETRIS_BOARD_HEIGHT 20

#include <vector>
#include "piece.hpp"


// represents the state of each board square
enum Tile {
    EMPTY,
    GHOST,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    LIGHTBLUE,
    MAGENTA
};


class Board {
protected:
    const static unsigned int width = TETRIS_BOARD_WIDTH;
    const static unsigned int height = TETRIS_BOARD_HEIGHT;
    std::vector<Tile> board;

public:
    Board();

    inline unsigned int getWidth() { return width; }
    inline unsigned int getHeight() { return height; }
    //inline std::vector<Tile> getBoard() { return board; }
};


class Game : Board {
private:
    unsigned int score = 0;
    unsigned int level = 1;
    unsigned int combo = 0;
    Piece held, current;
    std::vector<Piece> queue;

public:
    Game();

    inline unsigned int getScore() { return score; }
    inline unsigned int getLevel() { return level; }
    inline unsigned int getCombo() { return combo; }
};

#endif
