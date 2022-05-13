#include "raylib-cpp.hpp"

const uint boardSize = 19;
const uint paddingAmount = 40;
const uint tileSize = 40;
const uint stoneRadius = 15;

// This -1 is because Go is played on the tile corners, rather than the insides
const uint screenSize = (boardSize - 1) * tileSize + 2 * paddingAmount;

enum class Stone {
  Black, White, None
};

Stone currentPlayer = Stone::Black;
std::vector<std::vector<Stone>> board(boardSize, std::vector<Stone>(boardSize, Stone::None));

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

  for (uint i = 0; i < boardSize; i++) {
    for (uint j = 0; j < boardSize; j++) {
      if (board[i][j] == Stone::None) continue;

      Color color = (board[i][j] == Stone::White) ? RAYWHITE : BLACK;
      DrawCircle(paddingAmount + tileSize * i, paddingAmount + tileSize * j, stoneRadius, color);
    }
  }

  BoardCoordinates currentPosition = BoardCoordinates::fromScreenXY(GetMousePosition());
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