#include "../board.cpp"
#include "ChessPiece.cpp"
#include "RookPiece.cpp"
#include "KnightPiece.cpp"
#include "QueenPiece.cpp"
#include "BishopPiece.cpp"
#include "../game.cpp" // For promotionFlag
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

class PawnPiece : public ChessPiece
{
public:
  bool firstMove = true;
  bool enPassant = false;
  int direction;

  PawnPiece(bool color, int row, int col, Board *board, std::vector<ChessPiece *> &pieces)
      : ChessPiece(color, row, col, board, pieces)
  {
    // path = "./../assets/pieces/" + pathColor + "/pawn.png";
    direction = (row == 6) ? 1 : -1;
  }

  bool isBlocked(int row, int col)
  {
    int coldiff = this->col - col;
    if (coldiff == 0)
    {
      return board->state[row][col] != nullptr;
    }
    else
    {
      if (board->state[row][col] != nullptr && board->state[row][col]->color != this->color)
      {
        return true;
      }
    }
    return false;
  }

  bool moveRules(int row, int col)
  {
    return true;
  }

  void promote()
  {
    int choice = -1;
    while (choice == -1)
    {
      std::cout << "Choose a piece to promote to (0: Rook, 1: Knight, 2: Queen, 3: Bishop): ";
      std::cin >> choice;
      switch (choice)
      {
      case 0:
        pieces.push_back(board->state[row][col] = new RookPiece(this->color, row, col, board, pieces));
        pieces.erase(std::remove(pieces.begin(), pieces.end(), this), pieces.end());
        break;
      case 1:
        pieces.push_back(board->state[row][col] = new KnightPiece(this->color, row, col, board, pieces));
        pieces.erase(std::remove(pieces.begin(), pieces.end(), this), pieces.end());
        break;
      case 2:
        pieces.push_back(board->state[row][col] = new QueenPiece(this->color, row, col, board, pieces));
        pieces.erase(std::remove(pieces.begin(), pieces.end(), this), pieces.end());
        break;
      case 3:
        pieces.push_back(board->state[row][col] = new BishopPiece(this->color, row, col, board, pieces));
        pieces.erase(std::remove(pieces.begin(), pieces.end(), this), pieces.end());
        break;
      default:
        choice = -1; // Invalid choice
      }
    }
    Game::promotionFlag = false;
  }

  bool canMove(int row, int col, std::vector<ChessPiece *> &pieces, bool r)
  {
    if (!ChessPiece::canMove(row, col, pieces, r))
      return false;

    int rowdiff = this->row - row;
    int coldiff = this->col - col;

    if (row + direction < 0 || row + direction > 7)
      return false;

    ChessPiece *piece = board->state[row + direction][col];
    if (piece && std::abs(coldiff) == 1 && piece->path.find("/pawn") != std::string::npos)
    {
      PawnPiece *pawnPiece = dynamic_cast<PawnPiece *>(piece);
      if (pawnPiece && pawnPiece->color != this->color && Game::moveNumber - pawnPiece->lastMoveNumber == 1 &&
          pawnPiece->enPassant && this->row == (color ? 3 : 4))
      {
        board->remove(row + direction, col);
        return true;
      }
    }

    if (rowdiff == direction && coldiff == 0)
    {
      if (isBlocked(this->row - direction, col))
        return false;
      if (enPassant)
        enPassant = false;
      if (row == (color ? 0 : 7))
        Game::promotionFlag = true;
      return true;
    }

    if (rowdiff == 2 * direction && firstMove && coldiff == 0)
    {
      if (isBlocked(this->row - direction, col) || isBlocked(this->row - 2 * direction, col))
        return false;
      if (!enPassant && firstMove)
        enPassant = true;
      return true;
    }

    if (rowdiff == direction && std::abs(coldiff) == 1)
    {
      if (board->state[row][col] != nullptr && board->state[row][col]->color != this->color)
      {
        if (row == (this->direction == 1 ? 0 : 7))
          Game::promotionFlag = true;
        return true;
      }
      if (enPassant)
        enPassant = false;
      return false;
    }

    return false;
  }

private:
  std::string path;
  // Add image variable if using graphics library
};
