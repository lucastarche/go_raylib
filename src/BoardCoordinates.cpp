#include "BoardCoordinates.h"
#include "Constants.h"

BoardCoordinates::BoardCoordinates(int x, int y) : x(x), y(y) {}

BoardCoordinates BoardCoordinates::fromScreenPos(Vector2 pos) {
  int x = static_cast<int>((pos.x - paddingAmount + stoneRadius) / tileSize);
  int y = static_cast<int>((pos.y - paddingAmount + stoneRadius) / tileSize);

  if (x < 0) { x = 0; }
  if (x >= boardSize) { x = boardSize - 1; }

  if (y < 0) { y = 0; }
  if (y >= boardSize) { y = boardSize - 1; }

  return {x, y};
}