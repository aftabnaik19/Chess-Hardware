#include <bits/stdc++.h>
class Move
{
private:
  std::vector<int> prevPosition;
  std::vector<int> currPosition;

public:
  Move() : prevPosition(2, -1), currPosition(2, -1) {}

  void setPrevPosition(int row, int col)
  {
    prevPosition[0] = row;
    prevPosition[1] = col;
  }

  void setCurrPosition(int row, int col)
  {
    currPosition[0] = row;
    currPosition[1] = col;
  }

  std::vector<int> getPrevPosition() const
  {
    return prevPosition;
  }

  std::vector<int> getCurrPosition() const
  {
    return currPosition;
  }
};
