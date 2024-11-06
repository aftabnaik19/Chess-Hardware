#include "../board.cpp"   // Replace with actual path if needed
#include "ChessPiece.cpp" // Replace with actual path if needed
#include <vector>
#include <cmath>
#include <string>

class QueenPiece : public ChessPiece
{
public:
  QueenPiece(bool color, int row, int col, Board *board, std::vector<ChessPiece *> &pieces)
      : ChessPiece(color, row, col, board, pieces)
  {
    // path = "./../assets/pieces/" + pathColor + "/queen.png";
    // Initialize image if using graphics library
  }

  bool isBlocked(int row, int col)
  {
    int rowdiff = this->row - row;
    int coldiff = this->col - col;
    int checkrow, checkcol;

    // Moving diagonally to bottom-right
    if (rowdiff > 0 && coldiff < 0)
    {
      checkcol = this->col + 1;
      checkrow = this->row - 1;
      for (; checkrow > row; checkrow--, checkcol++)
      {
        if (board->state[checkrow][checkcol] != nullptr)
          return true;
      }
    }
    // Moving diagonally to top-left
    else if (rowdiff > 0 && coldiff > 0)
    {
      checkcol = this->col - 1;
      checkrow = this->row - 1;
      for (; checkrow > row; checkrow--, checkcol--)
      {
        if (board->state[checkrow][checkcol] != nullptr)
          return true;
      }
    }
    // Moving diagonally to bottom-left
    else if (rowdiff < 0 && coldiff < 0)
    {
      checkcol = this->col + 1;
      checkrow = this->row + 1;
      for (; checkrow < row; checkrow++, checkcol++)
      {
        if (board->state[checkrow][checkcol] != nullptr)
          return true;
      }
    }
    // Moving diagonally to top-right
    else if (rowdiff < 0 && coldiff > 0)
    {
      checkcol = this->col - 1;
      checkrow = this->row + 1;
      for (; checkrow < row; checkrow++, checkcol--)
      {
        if (board->state[checkrow][checkcol] != nullptr)
          return true;
      }
    }
    // Moving vertically down
    else if (coldiff == 0 && rowdiff > 0)
    {
      checkrow = this->row - 1;
      checkcol = this->col;
      for (; checkrow > row; checkrow--)
      {
        if (board->state[checkrow][checkcol] != nullptr)
          return true;
      }
    }
    // Moving vertically up
    else if (coldiff == 0 && rowdiff < 0)
    {
      checkrow = this->row + 1;
      checkcol = this->col;
      for (; checkrow < row; checkrow++)
      {
        if (board->state[checkrow][checkcol] != nullptr)
          return true;
      }
    }
    // Moving horizontally to the left
    else if (rowdiff == 0 && coldiff > 0)
    {
      checkrow = this->row;
      checkcol = this->col - 1;
      for (; checkcol > col; checkcol--)
      {
        if (board->state[checkrow][checkcol] != nullptr)
          return true;
      }
    }
    // Moving horizontally to the right
    else if (rowdiff == 0 && coldiff < 0)
    {
      checkrow = this->row;
      checkcol = this->col + 1;
      for (; checkcol < col; checkcol++)
      {
        if (board->state[checkrow][checkcol] != nullptr)
          return true;
      }
    }
    return false;
  }

  bool moveRules(int row, int col)
  {
    int rowdiff = std::abs(this->row - row);
    int coldiff = std::abs(this->col - col);
    if (rowdiff == 0 && coldiff == 0)
      return false;
    return (rowdiff > 0 != coldiff > 0) || (rowdiff == coldiff);
  }

  bool canMove(int row, int col, std::vector<ChessPiece *> &pieces, bool r)
  {
    if (!ChessPiece::canMove(row, col, pieces, r))
      return false;
    if (!moveRules(row, col))
      return false;
    if (isBlocked(row, col))
      return false;
    return true;
  }

private:
  std::string path;
  // Add image variable if using graphics library
};
