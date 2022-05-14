#include "Board.h"

Board::Board() {
  currentPlayer = Stone::Black;
  board = vector(boardSize, vector(boardSize, Stone::None));
}

void Board::placeStone(BoardCoordinates coordinates) {
  if (board[coordinates.x][coordinates.y] != Stone::None) return;

  board[coordinates.x][coordinates.y] = currentPlayer;
  togglePlayer();
}

void Board::togglePlayer() {
  currentPlayer =
      currentPlayer == Stone::Black
      ? Stone::White
      : Stone::Black;
}

Stone Board::getStoneAt(BoardCoordinates coordinates) {
  return board[coordinates.x][coordinates.y];
}

Stone Board::getStoneAt(int x, int y) {
  return board[x][y];
}