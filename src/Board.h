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
  void removeStone(BoardCoordinates coordinates);

 public:
  Board();
  void placeStone(BoardCoordinates coordinates);
  Stone getStoneAt(BoardCoordinates coordinates);
  Stone getStoneAt(int x, int y);

  int countLiberties(BoardCoordinates coordinates, Stone player);
  int countLibertiesAndGetComponent(vector<vector<bool>> &visited,
                                    vector<BoardCoordinates> &component,
                                    BoardCoordinates coordinates);
  void removeStonesWithNoLiberties();
};