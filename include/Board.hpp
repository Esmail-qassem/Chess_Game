#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

// Define the Board class here (the 8x8 grid, display, move logic)
#include<array>
#include<memory>
#include "Piece.hpp"
/*
std::array< std::array< std::unique_ptr<Piece> , 8> , 8>
           |            |                        |   |  |
           |            |                        |   |  +-- 8 rows
           |            |                        +---+-- each row has 8 cells
           |            +-- each cell is a smart pointer to a Piece
           +-- the whole thing is the board


*/
#define BOARD_ROWS 8u
#define BOARD_COLS 8u
class Board
{
    public : 
        Board();
        void initialize();	
        void display() const;	
        const Piece*  getPieceAt(const Position_t& pos)const;	
        bool movePiece(const Position_t& from, const Position_t& to) ;
        bool isInBounds(const Position_t& pos)const	;
        ~Board() = default;
    private : 
        std::array<std::array<std::unique_ptr<Piece>, 8>, 8> m_grid;
};
#endif
