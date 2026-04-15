#ifndef CHESS_TYPES_HPP
#define CHESS_TYPES_HPP

// Define your enums (Color, PieceType) and the Position struct here
enum class color_t
{
    white,
    black
};

enum class PieceType_t
{
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn
};

struct Position_t
{
    int row; // 0-7 for rows 1-8
    int col; // 0-7 for columns a-h
};    

#endif
