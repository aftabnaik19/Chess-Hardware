#include "../board.hpp"   // Replace with actual path if needed
#include "ChessPiece.cpp" // Replace with actual path if needed
#include <vector>
#include <cmath>
#include <string>

class KingPiece : public ChessPiece
{
public:
  KingPiece(bool color, int row, int col, Board *board, std::vector<ChessPiece *> &pieces)
      : ChessPiece(color, row, col, board, pieces)
  {
    // path = "./../assets/pieces/" + pathColor + "/king.png";
    // Load image if using a specific image library
  }

  bool inCheck(const std::vector<ChessPiece *> &pieces)
  {
    for (const auto &piece : pieces)
    {
      if (piece->color == this->color)
        continue;
      if (piece->canMove(this->row, this->col, pieces, false))
        return true;
    }
    return false;
  }

  bool checkMate(std::vector<ChessPiece *> &pieces)
  {
    for (auto &p : pieces)
    {
      if (p->color != this->color)
        continue;
      p->storePossibleMoves();
      if (!p->possibleMoves.empty())
      {
        std::cout << "returned false for checkmate\n";
        return false;
      }
    }
    return true;
  }

  bool canCastle(int row, int col)
  {
    int coldiff = this->col - col;
    if (this->lastMoveNumber == 0 && this->row == (color ? 7 : 0) && std::abs(coldiff) == 2)
    {
      if (coldiff > 0)
      {
        if (board->state[this->row][1] != nullptr || board->state[this->row][2] != nullptr || board->state[this->row][3] != nullptr)
          return false;
        if (board->state[this->row][0] != nullptr && board->state[this->row][0]->path.find("/rook") != std::string::npos &&
            board->state[this->row][0]->lastMoveNumber == 0)
        {
          board->state[this->row][0]->update(this->row, 3);
          return true;
        }
      }
      else
      {
        if (board->state[this->row][5] != nullptr || board->state[this->row][6] != nullptr)
          return false;
        if (board->state[this->row][7] != nullptr && board->state[this->row][7]->path.find("/rook") != std::string::npos &&
            board->state[this->row][7]->lastMoveNumber == 0)
        {
          board->state[this->row][7]->update(this->row, 5);
          return true;
        }
      }
    }
    return false;
  }

  bool moveRules(int row, int col)
  {
    int rowdiff = this->row - row;
    int coldiff = this->col - col;
    return (std::abs(rowdiff) | std::abs(coldiff)) == 1;
  }

  bool canMove(int row, int col, std::vector<ChessPiece *> &pieces, bool r)
  {
    if (!ChessPiece::canMove(row, col, pieces, r))
      return false;
    if (!moveRules(row, col))
      return false;
    if (canCastle(row, col))
      return true;
    return true;
  }

private:
  std::string path;
  // Add image variable if using graphics library
};
