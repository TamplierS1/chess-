#ifndef PIECE_H
#define PIECE_H

#include <string>

#include <raylib.h>

namespace Piece
{
enum class Kind
{
    Pawn,
    Bishop,
    Knight,
    Rook,
    Queen,
    King
};

struct Piece
{
    Vector2 pos;
    Kind kind;
    // This color only represents the team a piece belongs to.
    // And not its actual color.
    Color color;
    std::string texture_name;
};

}
#endif  // PIECE_H
