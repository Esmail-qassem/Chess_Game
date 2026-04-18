#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP
#include "Types.hpp"
#include <vector>

class Board; 
class Piece
{
    public :
        Piece(color_t c,PieceType_t p):color(c),PieceType(p){}
        virtual std::vector<Position_t>  getValidMoves (const Position_t& from, const Board& board) const = 0;
        // = 0 that mean that the base will not implement it but the deriverd
        virtual ~Piece() = default;
        virtual char getSymbol()const= 0;
        color_t getColor()const
        {
            return color;
        }
        PieceType_t getType()const
        {
            return PieceType;
        }
    protected : 
       color_t  color;
       PieceType_t PieceType;



};

class King : public Piece
{
    public:
        King(color_t c):Piece(c , PieceType_t::King){}
        std::vector<Position_t> getValidMoves(const Position_t& from, const Board& board) const override;
        char getSymbol()const override;

    private:

};
class Queen :public Piece
{
    public:
        Queen(color_t c):Piece(c , PieceType_t::Queen){}
        std::vector<Position_t> getValidMoves(const Position_t& from, const Board& board) const override;
        char getSymbol()const override;


    private:
};
class Rook : public Piece
{
    public:
        Rook(color_t c):Piece(c , PieceType_t::Rook){}
        std::vector<Position_t> getValidMoves(const Position_t& from, const Board& board) const override;
        char getSymbol()const override;


    private:
};

class Bishop : public Piece
{
    public:
        Bishop(color_t c):Piece(c , PieceType_t::Bishop){}
        std::vector<Position_t> getValidMoves(const Position_t& from, const Board& board) const override;
        char getSymbol()const override;


    private:
};

class Knight :public Piece
{
    public:
        Knight(color_t c):Piece(c , PieceType_t::Knight){}
        std::vector<Position_t> getValidMoves(const Position_t& from, const Board& board) const override;
        char getSymbol()const override;   


    private:
};

class Pawn :public Piece
{
    public:
        Pawn(color_t c):Piece(c , PieceType_t::Pawn){}
        std::vector<Position_t> getValidMoves(const Position_t& from, const Board& board) const override;
        char getSymbol()const override;  



    private:
};
#endif
