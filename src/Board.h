#pragma once
#include "Constants.h"
#include "BoardCoordinates.h"
#include <vector>

using std::vector;

class Board {
 private:
  Stone currentPlayer;
  vector<vector<Stone>> board;

  void togglePlayer();

 public:
  Board();
  void placeStone(BoardCoordinates coordinates);
  Stone getStoneAt(BoardCoordinates coordinates);
  Stone getStoneAt(int x, int y);
};