#include "raylib-cpp.hpp"
#include "src/Constants.h"
#include "src/BoardCoordinates.h"

enum class Stone {
  Black, White, None
};

Stone currentPlayer = Stone::Black;
std::vector<std::vector<Stone>> board;

void UpdateDrawFrame();

int main() {
  board = std::vector(screenSize, std::vector(screenSize, Stone::None));
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
  for (int i = 0; i < boardSize; i++) {
    int linePosition = (int) (paddingAmount + tileSize * i);
    DrawLine(linePosition, paddingAmount, linePosition, screenSize - paddingAmount, BLACK);
    DrawLine(paddingAmount, linePosition, screenSize - paddingAmount, linePosition, BLACK);
  }

  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (board[i][j] == Stone::None) continue;

      Color color = (board[i][j] == Stone::White) ? RAYWHITE : BLACK;
      DrawCircle(paddingAmount + tileSize * i, paddingAmount + tileSize * j, stoneRadius, color);
    }
  }

  BoardCoordinates currentPosition = BoardCoordinates::fromScreenPos(GetMousePosition());
  DrawCircleLines(paddingAmount + tileSize * currentPosition.x,
                  paddingAmount + tileSize * currentPosition.y,
                  stoneRadius,
                  RED);

  if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
    if (board[currentPosition.x][currentPosition.y] == Stone::None) {
      board[currentPosition.x][currentPosition.y] = currentPlayer;

      currentPlayer = (currentPlayer == Stone::Black) ? Stone::White : Stone::Black;
    }
  }

  EndDrawing();
}