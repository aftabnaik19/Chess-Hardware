#include <iostream>
#include <vector>
#include "../board.cpp"
#include "ChessPiece.cpp"

class RookPiece : public ChessPiece
{
public:
  RookPiece(bool color, int row, int col, Board &board, std::vector<ChessPiece *> &pieces)
      : ChessPiece(color, row, col, board, pieces)
  {
    // this->path = "./../assets/pieces/" + pathColor + "/rook" + ".png";
    // this->image = loadImage(path); // Assuming loadImage is a function to load images
  }

  bool isBlocked(int row, int col)
  {
    int rowdiff = this->row - row;
    int coldiff = this->col - col;
    int checkrow, checkcol;

    if (coldiff == 0 && rowdiff > 0)
    { // Moving upwards
      checkrow = this->row - 1;
      checkcol = this->col;
      for (; checkrow > row; --checkrow)
      {
        if (board.state[checkrow][checkcol] != nullptr)
        {
          return true;
        }
      }
    }
    else if (coldiff == 0 && rowdiff < 0)
    { // Moving downwards
      checkrow = this->row + 1;
      checkcol = this->col;
      for (; checkrow < row; ++checkrow)
      {
        if (board.state[checkrow][checkcol] != nullptr)
        {
          return true;
        }
      }
    }
    else if (rowdiff == 0 && coldiff > 0)
    { // Moving left
      checkrow = this->row;
      checkcol = this->col - 1;
      for (; checkcol > col; --checkcol)
      {
        if (board.state[checkrow][checkcol] != nullptr)
        {
          return true;
        }
      }
    }
    else if (rowdiff == 0 && coldiff < 0)
    { // Moving right
      checkrow = this->row;
      checkcol = this->col + 1;
      for (; checkcol < col; ++checkcol)
      {
        if (board.state[checkrow][checkcol] != nullptr)
        {
          return true;
        }
      }
    }
    return false;
  }

  bool moveRules(int row, int col)
  {
    int rowdiff = std::abs(this->row - row);
    int coldiff = std::abs(this->col - col);
    return !(rowdiff > 0 == coldiff > 0);
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
  // Image loadImage(const std::string &path)
  // {
  //   // Load image logic here
  // }
};
