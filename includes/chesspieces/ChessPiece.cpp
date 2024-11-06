#include <bits/stdc++.h>
#include "../board.cpp"
#include "Game.h"

class ChessPiece
{
public:
  int x, y;
  bool color;
  int row, col;
  std::string path;
  std::string pathColor;
  int lastMoveNumber = 0;
  Board *board;
  std::vector<std::vector<int>> possibleMoves;
  std::vector<ChessPiece *> pieces;
  std::mutex lock;

  ChessPiece(bool color, int row, int col, Board *board, const std::vector<ChessPiece *> &pieces)
      : color(color), row(row), col(col), board(board), pieces(pieces)
  {
    pathColor = color ? "white" : "black";
    x = getX(col);
    y = getY(row);
  }

  virtual ~ChessPiece() = default;

  void storePossibleMoves()
  {
    std::lock_guard<std::mutex> guard(lock);
    possibleMoves.clear();
    std::cout << "Possible moves of " << path << std::endl;

    for (int i = 0; i < Board::MAX_ROW; ++i)
    {
      for (int j = 0; j < Board::MAX_COL; ++j)
      {
        if (canMove(i, j, pieces, true))
        {
          std::cout << i << "  " << j << std::endl;
          possibleMoves.push_back({i, j});
        }
      }
    }
    Game::promotionFlag = false;
  }

  bool isPosition(int y, int x) const
  {
    return y == this->row && x == this->col;
  }

  void drag(int y, int x)
  {
    this->x = x - Board::SQUARE_SIZE / 2;
    this->y = y - Board::SQUARE_SIZE / 2;
  }

  virtual bool moveRules(int row, int col) = 0; // Pure virtual function for subclass implementations

  bool canMove(int row, int col, const std::vector<ChessPiece *> &pieces_original, bool r)
  {
    if (board->friendlyPieceAtPosition(row * Board::SQUARE_SIZE, col * Board::SQUARE_SIZE, this->color))
    {
      return false;
    }

    std::vector<ChessPiece *> pieces;
    for (auto *piece : pieces_original)
    {
      pieces.push_back(piece); // Shallow copy; deep copy might be needed for more complex logic
    }

    KingPiece *k = nullptr;
    for (auto *p : pieces)
    {
      if (p->path.find("king") != std::string::npos && p->color == this->color)
      {
        k = dynamic_cast<KingPiece *>(p);
      }
    }

    // Nalat check it once
    if (k && r)
    {
      int cur_row = this->row;
      int cur_col = this->col;
      ChessPiece *g = board->state[row][col];
      this->update(row, col);
      board->state[cur_row][cur_col] = nullptr;
      if (g)
      {
        pieces.erase(std::remove(pieces.begin(), pieces.end(), g), pieces.end());
      }
      board->state[row][col] = this;

      if (k->inCheck(pieces))
      {
        if (g)
        {
          pieces.push_back(g);
        }
        this->update(cur_row, cur_col);
        board->state[cur_row][cur_col] = this;
        board->state[row][col] = g;
        return false;
      }

      if (g)
      {
        pieces.push_back(g);
      }
      board->state[cur_row][cur_col] = this;
      board->state[row][col] = g;
      this->update(cur_row, cur_col);
    }

    return true;
  }

  void originalPosition()
  {
    x = getX(col);
    y = getY(row);
  }

  bool update(int newRow, int newCol)
  {
    col = newCol;
    row = newRow;
    x = getX(col);
    y = getY(row);
    return true;
  }

  int getX(int col) const
  {
    return col * Board::SQUARE_SIZE;
  }

  int getY(int row) const
  {
    return row * Board::SQUARE_SIZE;
  }

  // void draw(sf::RenderWindow &window)
  // { // Using SFML library; replace with actual drawing logic
  //   std::lock_guard<std::mutex> guard(lock);
  //   // window.draw(image, x, y);  // Modify as per your rendering approach
  // }

  int getCol(int x) const
  {
    return (x < 0 || x > 8 * Board::SQUARE_SIZE) ? col : x / Board::SQUARE_SIZE;
  }

  int getRow(int y) const
  {
    return (y < 0 || y > 8 * Board::SQUARE_SIZE) ? row : y / Board::SQUARE_SIZE;
  }
};
