#pragma once

#include <string>

#include <raylib.h>

enum class Kind
{
    Pawn,
    Bishop,
    Knight,
    Rook,
    Queen,
    King
};

class Piece
{
public:
    Piece(const Vector2& _pos, const Kind& _kind, const Color& _color,
          const std::string& _texture_name)
        : pos(_pos)
        , kind(_kind)
        , color(_color)
        , texture_name(_texture_name)
    {
    }

    Vector2 pos;
    Kind kind;
    // This color only represents the team a piece belongs to.
    // And not its actual color.
    Color color;
    std::string texture_name;
};
