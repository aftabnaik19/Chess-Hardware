#include "../board.cpp"   // Replace with actual path if needed
#include "ChessPiece.cpp" // Replace with actual path if needed
#include <vector>
#include <cmath>
#include <string>

class KnightPiece : public ChessPiece
{
public:
  KnightPiece(bool color, int row, int col, Board *board, std::vector<ChessPiece *> &pieces)
      : ChessPiece(color, row, col, board, pieces)
  {
    path = "./../assets/pieces/" + pathColor + "/knight.png";
    // Load image if using a specific image library
  }

  bool moveRules(int row, int col)
  {
    int rowdiff = std::abs(this->row - row);
    int coldiff = std::abs(this->col - col);
    if (rowdiff == 0 || coldiff == 0)
      return false;
    return (rowdiff + coldiff == 3);
  }

  bool canMove(int row, int col, std::vector<ChessPiece *> &pieces, bool r)
  {
    if (!ChessPiece::canMove(row, col, pieces, r))
      return false;
    if (!moveRules(row, col))
      return false;
    return true;
  }

private:
  std::string path;
  // Add image variable if using graphics library
};
