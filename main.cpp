#include "raylib-cpp.hpp"

const uint boardSize = 19;
const uint paddingAmount = 20;
const uint tileSize = 20;

const uint screenSize = boardSize * tileSize + 2 * paddingAmount;

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

  for (uint i = 0; i <= boardSize; i++) {
    int linePosition = (int) (paddingAmount + tileSize * i);
    DrawLine(linePosition, paddingAmount, linePosition, screenSize - paddingAmount, BLACK);
    DrawLine(paddingAmount, linePosition, screenSize - paddingAmount, linePosition, BLACK);
  }

  EndDrawing();
}