/* src/piece.hpp
 * created mon may 6 2024
 * by catroidvania
 */

#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdlib>
#include <ctime>


// helpful resource
// https://tetris.wiki/Super_Rotation_System


// enum to make it clear when we are referring to the type of piece
enum PieceType {
    I = 'I',
    O = 'O',
    S = 'S',
    Z = 'Z',
    L = 'L',
    J = 'J',
    T = 'T',
    NOPIECE = 'N'
};


// represents piece rotation states
enum PieceRotation {
    NONE,   // default state, no rotation
    RIGHT,  // right state
    FLIP,   // upside down
    LEFT    // left state
};


class Piece {
private:
    PieceType type;
    PieceRotation rotation;

public:
    Piece();
    Piece(PieceType init_type);
    //Piece(PieceType init_type, PieceRotation init_rotation);

    inline PieceType getType() { return type; }
};

#endif
