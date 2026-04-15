#ifndef CHESS_GAME_HPP
#define CHESS_GAME_HPP

#include "Board.hpp"



class Game
{
    public :
        Game();
        ~Game() = default;
        void run();
bool parseInput(const std::string& input, Position_t& from, Position_t& to) const;

    private :

        Board m_board;
        color_t m_currentTurn;
        bool m_isRunning;

};







#endif
