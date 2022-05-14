#pragma once
#include "raylib-cpp.hpp"

struct BoardCoordinates {
  int x;
  int y;

  BoardCoordinates(int x, int y);
  static BoardCoordinates fromScreenPos(Vector2 pos);
};