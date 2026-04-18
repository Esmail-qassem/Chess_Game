#include <string>
#include <iostream>
#include <vector>
#include "Game.hpp"
std::vector<std::string> History;
Game::Game()
{
    m_currentTurn = color_t::white;
    m_isRunning = true;
}

bool Game::parseInput(const std::string &input, Position_t &from, Position_t &to) const
{
    bool status = false;

    if (input.size() == 5 && input[2] == ' ')
    {
        from.col = input[0] - 'a'; // a8
        from.row = input[1] - '1';

        to.col = input[3] - 'a'; // a8
        to.row = input[4] - '1';
        status = true;
    }
    return status;
}
void Game::run()
{
    std::string input;
    std::vector<Position_t> moves;
    bool moved = false;
    bool check = false;
    Position_t whiteKing;
    Position_t BlackKing;
    Position_t *king_pointer;
    int counter = 0;
    while (m_isRunning)
    {
        if (m_currentTurn == color_t::white)
            std::cout << "White's turn: ";
        else
            std::cout << "Black's turn: ";
        std::getline(std::cin, input);
        if (input == "quit")
        {
            m_isRunning = false;
            break;
        }
        Position_t from, to;
        if (!parseInput(input, from, to))
        {
            std::cout << "Invalid input\n";
            continue;
        }
        if (check == true)
        {
            if (from.row != king_pointer->row || from.col != king_pointer->col)
            {
                std::cout << "You are in check! Move your king.\n";
                continue;
            }
        }
        const Piece *piece = m_board.getPieceAt(from);
        if (piece == nullptr)
        {
            std::cout << "No piece there\n";
            continue;
        }
        if (piece->getColor() != m_currentTurn)
        {
            std::cout << "Not your piece\n";
            continue;
        }
        moves = piece->getValidMoves(from, m_board);
        for (int i = 0; i < moves.size(); i++)
        {
            if (to.col == moves[i].col && to.row == moves[i].row)
            {
                counter++;
                std::cout << "valid position\n";
                m_board.movePiece(from, to);
                std ::string temp = (std::to_string(counter)) + ". " + input.substr(0, 2) + " " + input.substr(3, 2);
                History.push_back(temp);
                moved = true;
                check = false;
                break;
            }
        }
        if (moved == true)
        {
            for (char i = 0; i < BOARD_ROWS; i++)
            {
                for (char j = 0; j < BOARD_COLS; j++)
                {
                    Position_t temp = {i, j};
                    const Piece *Attacked_King = m_board.getPieceAt(temp);
                    if (Attacked_King != nullptr)
                    {
                        if (Attacked_King->getColor() != m_currentTurn)
                        {
                            // white
                            if (Attacked_King->getSymbol() == 'K')
                            {
                                whiteKing = temp;
                            }
                            else if (Attacked_King->getSymbol() == 'k') // black
                            {
                                BlackKing = temp;
                            }
                        }
                    }
                }
            }
            if (m_currentTurn == color_t::white)
            {
                m_currentTurn = color_t::black;
                king_pointer = &BlackKing;
            }
            else
            {
                m_currentTurn = color_t::white;
                king_pointer = &whiteKing;
            }
            for (char i = 0; i < BOARD_ROWS; i++)
            {
                for (char j = 0; j < BOARD_COLS; j++)
                {
                    Position_t tt = {i, j};
                    const Piece *to_piece = m_board.getPieceAt(tt);
                    if (to_piece != nullptr && to_piece->getColor() != m_currentTurn)
                    {
                        moves = to_piece->getValidMoves(tt, m_board);
                        for (int z = 0u; z < moves.size(); z++)
                        {
                            if ((moves[z].row == king_pointer->row) && (moves[z].col == king_pointer->col))
                            {
                                std::cout << "\ncheck\n";
                                check = true;
                            }
                        }
                    }
                }
            }
            m_board.display();
            moved = false;
        }
        else
        {
            std::cout << "Invalid move\n"; // ← this is missing
        }
    }
}