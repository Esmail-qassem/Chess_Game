#include "Piece.hpp"
#include "Board.hpp"

char King::getSymbol()const
{
    if(color == color_t ::white)
    {
        return 'K';
    }
    else
    {
        return 'k';
    }
}
std::vector<Position_t> King::getValidMoves(const Position_t& from, const Board& board) const 
{
    std::vector<Position_t>moves;
int offsets[8][2] = {
    { 1,  0},
    { 1,  1},
    { 1, -1},
    { 0,  1},
    { 0, -1},
    {-1,  0},
    {-1, -1},
    {-1,  1}
};


for(int i = 0; i < 8; i++)
{
    Position_t newPos;
    newPos.col = from.col + offsets[i][0];
    newPos.row = from.row + offsets[i][1];

    if(board.isInBounds(newPos))
    {
      const Piece *Target = board.getPieceAt(newPos);
      if(Target == nullptr || Target->getColor() != this->getColor())
      {
        moves.push_back(newPos);
      }
    }
}
return moves;
}
/*==============================================================================*/

char Queen::getSymbol()const
{
    if(color == color_t ::white)
    {
        return 'Q';
    }
    else
    {
        return 'q';
    }
}


std::vector<Position_t> Queen::getValidMoves(const Position_t& from, const Board& board) const 
{
    std::vector<Position_t>moves;
int directions[8][2] = {
    { 0,  1}, { 0, -1},  // up, down
    { 1,  0}, {-1,  0},  // right, left
    { 1,  1}, {-1, -1},  // diagonals
    { 1, -1}, {-1,  1}
};


for(int i=0;i<8;i++)
{
    Position_t newPos = from;
    while(true)
    {
        newPos.row +=  directions[i][0];
        newPos.col +=  directions[i][1];
        if(!board.isInBounds(newPos))
        {
            break;
        }
        const Piece *Target = board.getPieceAt(newPos);
        if(Target == nullptr )
        {
          moves.push_back(newPos);
        }
        else if(Target->getColor() != this->getColor())
        {
            moves.push_back(newPos);
            break;

        }
        else
        {
            break;
        }
    }

}
return moves;
}

/*==============================================================================*/

char Rook::getSymbol()const
{
    if(color == color_t ::white)
    {
        return 'R';
    }
    else
    {
        return 'r';
    }
}




std::vector<Position_t> Rook::getValidMoves(const Position_t& from, const Board& board) const 
{
    std::vector<Position_t>moves;
int directions[4][2] = {
    { 0,  1}, { 0, -1},  // up, down
    { 1,  0}, {-1,  0},  // right, left
};


for(int i=0;i<4;i++)
{
    Position_t newPos = from;
    while(true)
    {
        newPos.row +=  directions[i][0];
        newPos.col +=  directions[i][1];
        if(!board.isInBounds(newPos))
        {
            break;
        }
        const Piece *Target = board.getPieceAt(newPos);
        if(Target == nullptr )
        {
          moves.push_back(newPos);
        }
        else if(Target->getColor() != this->getColor())
        {
            moves.push_back(newPos);
            break;

        }
        else
        {
            break;
        }
    }

}
return moves;
}








/*==============================================================================*/

char Bishop::getSymbol()const
{
    if(color == color_t ::white)
    {
        return 'B';
    }
    else
    {
        return 'b';
    }
}



std::vector<Position_t> Bishop::getValidMoves(const Position_t& from, const Board& board) const 
{
    std::vector<Position_t>moves;
int directions[4][2] = {
    { 1,  1}, {-1, -1},  // diagonals
    { 1, -1}, {-1,  1}
};


for(int i=0;i<4;i++)
{
    Position_t newPos = from;
    while(true)
    {
        newPos.row +=  directions[i][0];
        newPos.col +=  directions[i][1];
        if(!board.isInBounds(newPos))
        {
            break;
        }
        const Piece *Target = board.getPieceAt(newPos);
        if(Target == nullptr )
        {
          moves.push_back(newPos);
        }
        else if(Target->getColor() != this->getColor())
        {
            moves.push_back(newPos);
            break;

        }
        else
        {
            break;
        }
    }

}
return moves;
}









/*==============================================================================*/

char Knight::getSymbol()const
{
    if(color == color_t ::white)
    {
        return 'N';
    }
    else
    {
        return 'n';
    }
}


std::vector<Position_t> Knight::getValidMoves(const Position_t& from, const Board& board) const 
{
    std::vector<Position_t>moves;
int directions[8][2] = {
    { 2,  1}, { 2, -1},  
    { 1,  2}, {1,  -2},  
    { -2,  1}, { -2, -1},  
    { -1,  -2}, {-1,  2} 
};


for(int i=0;i<8;i++)
{
        Position_t newPos = from;
        newPos.row +=  directions[i][0];
        newPos.col +=  directions[i][1];
        if(board.isInBounds(newPos))
        {
          const Piece *Target = board.getPieceAt(newPos);
          if(Target == nullptr || Target->getColor() != this->getColor())
          {
            moves.push_back(newPos);
          }
        }
}
return moves;
}

/*==============================================================================*/

char Pawn::getSymbol()const
{
    if(color == color_t ::white)
    {
        return 'P';
    }
    else
    {
        return 'p';
    }
}


std::vector<Position_t> Pawn::getValidMoves(const Position_t& from, const Board& board) const 
{
    std::vector<Position_t>moves;
    Position_t newPos = from;
    if(this->getColor() == color_t::white)
    {
        if(newPos.row==1u)
        {
            Position_t oneStep = {from.row + 1, from.col};
             Position_t capture = {from.row + 1, from.col-1};
            Position_t capture2 = {from.row + 1, from.col+1};

            if(board.getPieceAt(oneStep) == nullptr)  // one step clear?
                {
                    Position_t twoStep = {from.row + 2, from.col};
                    if(board.isInBounds(twoStep) && board.getPieceAt(twoStep) == nullptr)
                        moves.push_back(twoStep);
            
                    moves.push_back(oneStep);  // also add one step
                }
            if(board.isInBounds(capture) && board.getPieceAt(capture) != nullptr) 
            {
                const Piece *Target = board.getPieceAt(capture);
                if(Target->getColor()!=this->getColor())
                {
                  moves.push_back(capture);  
                }

            }
            if(board.isInBounds(capture2) && board.getPieceAt(capture2) != nullptr) 
            {
                const Piece *Target = board.getPieceAt(capture2);
                if(Target->getColor()!=this->getColor())
                {
                  moves.push_back(capture2);  
                }                
                
            }                

        }
        else
        {
            newPos.row+=1;
            Position_t capture =  {newPos.row,from.col-1u};
            Position_t capture2 = {newPos.row,from.col+1u};


            if(board.isInBounds(newPos))
            {
                const Piece *Target = board.getPieceAt(newPos);
                if(Target == nullptr)
                {
                  moves.push_back(newPos);
                }
            }
            if(board.isInBounds(capture) && board.getPieceAt(capture) != nullptr) 
            {
                const Piece *Target = board.getPieceAt(capture);
                if(Target->getColor()!=this->getColor())
                {
                  moves.push_back(capture);  
                }

            }
            if(board.isInBounds(capture2) && board.getPieceAt(capture2) != nullptr) 
            {
                const Piece *Target = board.getPieceAt(capture2);
                if(Target->getColor()!=this->getColor())
                {
                  moves.push_back(capture2);  
                }                
                
            }    
        }
    }
    else
    {
        if(newPos.row==6u)
        {
            Position_t oneStep = {from.row - 1, from.col};
            Position_t capture = {from.row - 1, from.col-1};
            Position_t capture2 = {from.row - 1, from.col+1};
            if(board.getPieceAt(oneStep) == nullptr)  // one step clear?
                {
                    Position_t twoStep = {from.row - 2, from.col};
                    if(board.isInBounds(twoStep) && board.getPieceAt(twoStep) == nullptr)
                        moves.push_back(twoStep);
            
                    moves.push_back(oneStep);  // also add one step
                }
            if(board.isInBounds(capture) && board.getPieceAt(capture) != nullptr) 
            {
                const Piece *Target = board.getPieceAt(capture);
                if(Target->getColor()!=this->getColor())
                {
                  moves.push_back(capture);  
                }

            }
            if(board.isInBounds(capture2) && board.getPieceAt(capture2) != nullptr) 
            {
                const Piece *Target = board.getPieceAt(capture2);
                if(Target->getColor()!=this->getColor())
                {
                  moves.push_back(capture2);  
                }                
                
            }                
        }
        else
        {
           newPos.row-=1; 
            Position_t capture =  {newPos.row,from.col-1u};
            Position_t capture2 = {newPos.row,from.col+1u};

            if(board.isInBounds(newPos))
            {
                const Piece *Target = board.getPieceAt(newPos);
                if(Target == nullptr)
                {
                  moves.push_back(newPos);
                }

            }   
            if(board.isInBounds(capture) && board.getPieceAt(capture) != nullptr) 
            {
                const Piece *Target = board.getPieceAt(capture);
                if(Target->getColor()!=this->getColor())
                {
                  moves.push_back(capture);  
                }

            }
            if(board.isInBounds(capture2) && board.getPieceAt(capture2) != nullptr) 
            {
                const Piece *Target = board.getPieceAt(capture2);
                if(Target->getColor()!=this->getColor())
                {
                  moves.push_back(capture2);  
                }                
                
            }                 
        }

    }
return moves;
}
