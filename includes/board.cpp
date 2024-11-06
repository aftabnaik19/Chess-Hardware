#include <bits/stdc++.h>
#include "chesspieces/ChessPiece.cpp"
class Board
{
public:
  static const int SQUARE_SIZE = 120;
  static const int MAX_COL = 8;
  static const int MAX_ROW = 8;
  ChessPiece *state[MAX_ROW][MAX_COL] = {NULLptr};
  std::vector<ChessPiece *> pieces;
  bool blackCheck = false;
  bool whiteCheck = false;
  int activeBlockCol;
  int activeBlockRow;
  bool showPromotionWindow = false;
  Board(const std::vector<ChessPiece *> &pieces) : pieces(pieces) {}
  void setActiveBlock(int y, int x)
  {
    if (getRow(y) < 0 || getRow(y) > 7 || getCol(x) < 0 || getCol(x) > 7)
    {
      return;
    }
    activeBlockCol = getCol(x);
    activeBlockRow = getCol(y);
  }
  void updateActiveBlock(int y, int x)
  {
    if (getRow(y) < 0 || getRow(y) > 7 || getCol(x) < 0 || getCol(x) > 7)
      return;
    // pieces.remove(state[activeBlockRow][activeBlockCol]);
    state[getRow(y)][getCol(x)] = state[activeBlockRow][activeBlockCol];
    state[activeBlockRow][activeBlockCol] = NULL;
  }
  ChessPiece pieceAtPosition(int y, int x)
  {
    if (getRow(y) < 0 || getRow(y) > 7 || getCol(x) < 0 || getCol(x) > 7)
      return NULL;
    return state[getRow(y)][getCol(x)];
  }
  ChessPiece friendlyPieceAtPosition(int y, int x, bool friendlyPieceColor)
  {
    if (getRow(y) < 0 || getRow(y) > 7 || getCol(x) < 0 || getCol(x) > 7)
      return NULL;
    ChessPiece piece = state[getRow(y)][getCol(x)];
    if (piece == NULL)
      return NULL;
    if (piece.color != friendlyPieceColor)
      return NULL;
    return state[getRow(y)][getCol(x)];
  }
  ChessPiece enemyPieceAtPosition(int y, int x, bool friendlyPieceColor)
  {
    if (getRow(y) < 0 || getRow(y) > 7 || getCol(x) < 0 || getCol(x) > 7)
      return NULL;
    ChessPiece piece = state[getRow(y)][getCol(x)];
    if (piece == NULL)
      return NULL;
    if (piece.color == friendlyPieceColor)
    {
      return NULL;
    }
    return state[getRow(y)][getCol(x)];
  }

  int getCol(int x)
  {
    return x / SQUARE_SIZE;
  }
  int getRow(int y)
  {
    return y / SQUARE_SIZE;
  }
  void remove(int row, int col)
  {
    auto it = std::find(pieces.begin(), pieces.end(), state[row][col]);
    if (it != pieces.end())
    {
      pieces.erase(it);
    }
    state[row][col] = nullptr;
  }
};