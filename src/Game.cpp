#include <string>
#include <iostream>
#include <vector>
#include "Game.hpp"

Game::Game()
{
    m_currentTurn = color_t::white;
    m_isRunning = true;
}

bool Game::parseInput(const std::string& input, Position_t& from, Position_t& to) const
{
    bool status=false;

   if(input.size() == 5 && input[2] == ' ')
   {
        from.col= input[0]-'a';     //a8
        from.row= input[1]-'1';

        to.col= input[3]-'a';     //a8
        to.row= input[4]-'1';
        status = true;
   }
    return status;
}
void Game::run ()
{
    std::string input;
     std::vector<Position_t>moves; 
     bool moved = false;
    while(m_isRunning)
    {
        if(m_currentTurn == color_t::white)
            std::cout << "White's turn: ";
        else
            std::cout << "Black's turn: ";
                std::getline(std::cin,input);
        if(input == "quit")
        {
            m_isRunning =false;
            break;
        }
        Position_t from,to;
        if(!parseInput(input, from, to))
        {
            std::cout<<"Invalid input\n";
           continue; 
        }
        const Piece* piece = m_board.getPieceAt(from);
        if(piece == nullptr){std::cout<<"No piece there\n";continue;}
        if(piece->getColor()!=m_currentTurn ){std::cout<<"Not your piece\n";continue;}
        moves= piece->getValidMoves(from, m_board);
        for(int i =0; i<moves.size();i++)
        {
            if(to.col == moves[i].col  && to.row == moves[i].row)
            {
                std::cout<<"valid position\n";

                m_board.movePiece(from, to);
                moved= true;
                break;
            }
        }
        if(moved == true)
        {
            m_currentTurn = (m_currentTurn == color_t::white) ? color_t::black : color_t::white;
        }
        else
        {
            std::cout << "Invalid move\n";  // ← this is missing

        }
        m_board.display();    
    }

}