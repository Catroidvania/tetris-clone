/* src/board.cpp
 * created fri may 3 2024
 * by catroidvania
 */

#include "board.hpp"

Board::Board() {
    this->board = std::vector<Tile>(this->width * this->height, EMPTY);
}

bool Board::drawBoard(SDL_Surface* destSurface, int x, int y) {

    bool success = true;
    SDL_Surface* texture = nullptr;
    SDL_Rect coords = {0};

    for (int r = 0; r < this->height; r++) {
        for (int c = 0; c < this->width; c++) {
            coords = {c * TILE_SIZE + x, r * TILE_SIZE + y, 0, 0};

            switch (this->board[POINT(c, r, 10)]) {
            case EMPTY:
            case GHOST:
                texture = EMPTYBOARDTEXTURE;
                break;
            case RED:
                texture = ZPIECETEXTURE;
                break;
            case ORANGE:
                texture = LPIECETEXTURE;
                break;
            case YELLOW:
                texture = OPIECETEXTURE;
                break;
            case GREEN:
                texture = SPIECETEXTURE;
                break;
            case BLUE:
                texture = JPIECETEXTURE;
                break;
            case LIGHTBLUE:
                texture = IPIECETEXTURE;
                break;
            case MAGENTA:
                texture = TPIECETEXTURE;
                break;
            }

            success = SDL_BlitSurface(texture, nullptr, destSurface, &coords) > 0;
        }
    }

    return success;
}
