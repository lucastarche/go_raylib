#pragma once
#include "Constants.h"
#include "BoardCoordinates.h"
#include <array>
#include <vector>

using std::array;
using std::vector;

class Board {
 private:
  Stone currentPlayer;
  array<array<Stone, boardSize>, boardSize> board{};
  array<array<Stone, boardSize>, boardSize> koBoard{};

  void togglePlayer();
  void removeStone(BoardCoordinates coordinates);

 public:
  Board();
  void placeStone(BoardCoordinates coordinates);
  Stone getStoneAt(BoardCoordinates coordinates);
  Stone getStoneAt(int x, int y);

  int countLiberties(BoardCoordinates coordinates);
  int countLibertiesAndGetComponent(array<array<bool, boardSize>, boardSize> &visited,
                                    vector<BoardCoordinates> &component,
                                    BoardCoordinates coordinates);
  void removeStonesWithNoLiberties();
};