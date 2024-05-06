/* src/piece.cpp
 * created mon may 6 2024
 * by catroidvania
 */

#include "piece.hpp"


Piece::Piece() {
    this->rotation = NONE;

    switch (std::rand() % 7) {
    case 0:
        this->type = I;
        break;
    case 1:
        this->type = O;
        break;
    case 2:
        this->type = S;
        break;
    case 3:
        this->type = Z;
        break;
    case 4:
        this->type = L;
        break;
    case 5:
        this->type = J;
        break;
    case 6:
        this->type = T;
        break;
    default:
        this->type = I;
    }
}


Piece::Piece(PieceType init_type) {
    this->rotation = NONE;
    this->type = init_type;
}
