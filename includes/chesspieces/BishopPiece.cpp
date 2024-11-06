#include <vector>
#include <cmath>
#include <string>
#include "../board.cpp"
#include "ChessPiece.cpp"
class Board;      // Forward declaration of Board class
class ChessPiece; // Forward declaration of ChessPiece class

class BishopPiece : public ChessPiece
{
public:
  BishopPiece(bool color, int row, int col, Board *board, std::vector<ChessPiece *> &pieces)
      : ChessPiece(color, row, col, board, pieces)
  {
    // path = "./../assets/pieces/" + pathColor + "/bishop.png";
    // Load image here if using a specific image library
  }

  bool isBlocked(int row, int col)
  {
    int rowdiff = this->row - row;
    int coldiff = this->col - col;
    int checkrow;
    int checkcol;

    if (rowdiff > 0 && coldiff < 0)
    {
      checkcol = this->col + 1;
      checkrow = this->row - 1;
      while (checkrow > row)
      {
        if (board->state[checkrow][checkcol] != nullptr)
        {
          return true;
        }
        checkrow--;
        checkcol++;
      }
    }
    else if (rowdiff > 0 && coldiff > 0)
    {
      checkcol = this->col - 1;
      checkrow = this->row - 1;
      while (checkrow > row)
      {
        if (board->state[checkrow][checkcol] != nullptr)
        {
          return true;
        }
        checkrow--;
        checkcol--;
      }
    }
    else if (rowdiff < 0 && coldiff < 0)
    {
      checkcol = this->col + 1;
      checkrow = this->row + 1;
      while (checkrow < row)
      {
        if (board->state[checkrow][checkcol] != nullptr)
        {
          return true;
        }
        checkrow++;
        checkcol++;
      }
    }
    else if (rowdiff < 0 && coldiff > 0)
    {
      checkcol = this->col - 1;
      checkrow = this->row + 1;
      while (checkrow < row)
      {
        if (board->state[checkrow][checkcol] != nullptr)
        {
          return true;
        }
        checkrow++;
        checkcol--;
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
    return rowdiff == coldiff;
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
};
