#include "raylib-cpp.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "src/Constants.h"
#include "src/BoardCoordinates.h"
#include "src/Board.h"

Board board;
bool isPlaying;

void UpdateDrawFrame();

int main() {
  isPlaying = true;
  raylib::Window window(screenSize, screenSize, "go but in raylib");

  SetTargetFPS(60);

  while (!window.ShouldClose()) {
    UpdateDrawFrame();
  }

  return 0;
}

void UpdateDrawFrame() {
  BeginDrawing();
  if (!isPlaying) {
    EndDrawing();
    return;
  }

  ClearBackground(LIGHTGRAY);

  // We have one line per possible place to play
  for (int i = 0; i < boardSize; i++) {
    int linePosition = (int) (paddingAmount + tileSize * i);
    DrawLine(linePosition, paddingAmount, linePosition, screenSize - paddingAmount, BLACK);
    DrawLine(paddingAmount, linePosition, screenSize - paddingAmount, linePosition, BLACK);
  }

  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      Stone stone = board.getStoneAt(i, j);
      if (stone == Stone::None) continue;

      Color color = (stone == Stone::White) ? RAYWHITE : BLACK;
      DrawCircle(paddingAmount + tileSize * i, paddingAmount + tileSize * j, stoneRadius, color);
    }
  }

  BoardCoordinates currentPosition = BoardCoordinates::fromScreenPos(GetMousePosition());
  DrawCircleLines(paddingAmount + tileSize * currentPosition.x,
                  paddingAmount + tileSize * currentPosition.y,
                  stoneRadius,
                  RED);

  if (GuiButton({screenSize / 2 - 100, screenSize - paddingAmount + 5, 200, paddingAmount - 10},
                "Forfeit")) {
    isPlaying = false;
    DrawRectangle(100, 100, screenSize - 200, screenSize - 200, RAYWHITE);
    DrawRectangleLines(100, 100, screenSize - 200, screenSize - 200, BLUE);

    if (board.getCurrentPlayer() == Stone::Black) {
      DrawText("White wins!", (screenSize - 220) / 2, (screenSize - 220) / 2, 40, BLACK);
    } else {
      DrawText("Black wins!", (screenSize - 220) / 2, (screenSize - 220) / 2, 40, BLACK);
    }

  } else if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
    board.placeStone(currentPosition);
  }

  EndDrawing();
}