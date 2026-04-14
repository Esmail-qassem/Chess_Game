#include "Board.hpp"

#include <iostream>

bool Board::isInBounds(const Position_t& pos)const
{
    bool Bound_Status = false;
    if((pos.row >= 0 && pos.row < BOARD_ROWS) && (pos.col >= 0 && pos.col < BOARD_COLS))
    {
        Bound_Status = true;
    }
    else
    {
        // do nothing
    }
    return Bound_Status;
}

const Piece*  Board::getPieceAt(const Position_t& pos)const
{
/*  Because unique_ptr can't be copied — only one owner allowed. If you returned it, you'd be transferring ownership out of the grid, and the cell would become nullptr. The piece would leave the board just by looking at it.

    .get() gives you a raw pointer to look at the piece without taking ownership. The unique_ptr still owns it, the piece stays on the board.

*/

   return m_grid[pos.row][pos.col].get();  //e6
}	


void Board::display() const
{
    for(char i=0;i<BOARD_ROWS ;i++)
    {
        for(char j =0; j <BOARD_COLS;j++)
        {
            if(m_grid[BOARD_ROWS-i-1u][j].get() == nullptr)
            {
                std::cout<<".";

            }
            else
            {
                std::cout<<m_grid[BOARD_ROWS-i-1u][j]->getSymbol();
            }


        }
        std::cout<<"\n";
    }

}	



void Board::initialize()
{
    for(char i= 0;i<BOARD_ROWS ;i++)
    {
        for(char j = 0; j <BOARD_COLS ;j++)
        {
            m_grid[i][j] = nullptr;

        }
    }

    m_grid[0][0] = std::make_unique<Rook>(color_t::white);
    m_grid[0][1] = std::make_unique<Knight>(color_t::white);
    m_grid[0][2] = std::make_unique<Bishop>(color_t::white);
    m_grid[0][3] = std::make_unique<Queen>(color_t::white);
    m_grid[0][4] = std::make_unique<King>(color_t::white);
    m_grid[0][5] = std::make_unique<Bishop>(color_t::white);
    m_grid[0][6] = std::make_unique<Knight>(color_t::white);
    m_grid[0][7] = std::make_unique<Rook>(color_t::white);
    m_grid[1][0] = std::make_unique<Pawn>(color_t::white);
    m_grid[1][1] = std::make_unique<Pawn>(color_t::white);
    m_grid[1][2] = std::make_unique<Pawn>(color_t::white);
    m_grid[1][3] = std::make_unique<Pawn>(color_t::white);
    m_grid[1][4] = std::make_unique<Pawn>(color_t::white);
    m_grid[1][5] = std::make_unique<Pawn>(color_t::white);
    m_grid[1][6] = std::make_unique<Pawn>(color_t::white);
    m_grid[1][7] = std::make_unique<Pawn>(color_t::white);

    m_grid[6][0] = std::make_unique<Pawn>(color_t::black);
    m_grid[6][1] = std::make_unique<Pawn>(color_t::black);
    m_grid[6][2] = std::make_unique<Pawn>(color_t::black);
    m_grid[6][3] = std::make_unique<Pawn>(color_t::black);
    m_grid[6][4] = std::make_unique<Pawn>(color_t::black);
    m_grid[6][5] = std::make_unique<Pawn>(color_t::black);
    m_grid[6][6] = std::make_unique<Pawn>(color_t::black);
    m_grid[6][7] = std::make_unique<Pawn>(color_t::black);

    m_grid[7][0] = std::make_unique<Rook>(color_t::black);
    m_grid[7][1] = std::make_unique<Knight>(color_t::black);
    m_grid[7][2] = std::make_unique<Bishop>(color_t::black);
    m_grid[7][3] = std::make_unique<Queen>(color_t::black);
    m_grid[7][4] = std::make_unique<King>(color_t::black);
    m_grid[7][5] = std::make_unique<Bishop>(color_t::black);
    m_grid[7][6] = std::make_unique<Knight>(color_t::black);
    m_grid[7][7] = std::make_unique<Rook>(color_t::black);
}	
Board::Board()
{
  initialize();
}

bool Board::movePiece(const Position_t& from, const Position_t& to)
{
if(!isInBounds(from) || !isInBounds(to))
{
    return false;
}
if(!m_grid[from.row][from.col])
{
    return false;
}
    // transfer ownership — captured piece auto-deleted
    m_grid[to.row][to.col] = std::move(m_grid[from.row][from.col]);
    return true;

}
