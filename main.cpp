#include "raylib-cpp.hpp"

const uint boardSize = 19;
const uint paddingAmount = 40;
const uint tileSize = 40;
const uint stoneRadius = 15;

// This -1 is because Go is played on the tile corners, rather than the insides
const uint screenSize = (boardSize - 1) * tileSize + 2 * paddingAmount;

struct BoardCoordinates {
  uint x;
  uint y;

  BoardCoordinates(uint x, uint y) : x(x), y(y) {}
  static BoardCoordinates fromScreenXY(Vector2 pos) {
    int x = static_cast<int>((pos.x - paddingAmount + stoneRadius) / tileSize);
    int y = static_cast<int>((pos.y - paddingAmount + stoneRadius) / tileSize);

    uint boardX = x, boardY = y;
    if (x < 0) { boardX = 0; } else if (x >= boardSize) { boardX = boardSize - 1; }
    if (y < 0) { boardY = 0; } else if (y >= boardSize) { boardY = boardSize - 1; }

    return {boardX, boardY};
  }
};

void UpdateDrawFrame();

int main() {
  raylib::Window window(screenSize, screenSize, "go but in raylib");

  SetTargetFPS(60);

  while (!window.ShouldClose()) {
    UpdateDrawFrame();
  }

  return 0;
}

void UpdateDrawFrame() {
  BeginDrawing();

  ClearBackground(LIGHTGRAY);

  // We have one line per possible place to play
  for (uint i = 0; i < boardSize; i++) {
    int linePosition = (int) (paddingAmount + tileSize * i);
    DrawLine(linePosition, paddingAmount, linePosition, screenSize - paddingAmount, BLACK);
    DrawLine(paddingAmount, linePosition, screenSize - paddingAmount, linePosition, BLACK);
  }

  BoardCoordinates center = BoardCoordinates::fromScreenXY(GetMousePosition());
  DrawCircleLines(paddingAmount + tileSize * center.x, paddingAmount + tileSize * center.y, stoneRadius, RED);

  EndDrawing();
}