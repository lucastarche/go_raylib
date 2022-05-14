#include "Board.h"
#include <stack>

Board::Board() {
  currentPlayer = Stone::Black;
  board = vector(boardSize, vector(boardSize, Stone::None));
}

void Board::placeStone(BoardCoordinates coordinates) {
  if (getStoneAt(coordinates) != Stone::None) return;
  if (countLiberties(coordinates, currentPlayer) == 0) return;

  board[coordinates.x][coordinates.y] = currentPlayer;
  togglePlayer();
}

void Board::removeStone(BoardCoordinates coordinates) {
  board[coordinates.x][coordinates.y] = Stone::None;
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

int Board::countLiberties(BoardCoordinates coordinates, Stone player) {
  int liberties = 0;

  static const int dx[] = {-1, 1, 0, 0};
  static const int dy[] = {0, 0, 1, -1};

  vector<vector<bool>> visited(boardSize, vector(boardSize, false));
  std::stack<BoardCoordinates> curr;
  curr.push(coordinates);
  while (!curr.empty()) {
    BoardCoordinates pos = curr.top();
    curr.pop();
    if (visited[pos.x][pos.y]) continue;
    visited[pos.x][pos.y] = true;

    for (int k = 0; k < 4; k++) {
      int x = pos.x + dx[k], y = pos.y + dy[k];
      if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) continue;
      if (getStoneAt(x, y) == Stone::None) {
        liberties++;
      } else if (getStoneAt(x, y) == player) {
        curr.push(BoardCoordinates(x, y));
      }
    }
  }

  return liberties;
}

int Board::countLibertiesAndGetComponent(vector<vector<bool>> &visited,
                                         vector<BoardCoordinates> &component,
                                         BoardCoordinates coordinates) {
  int liberties = 0;

  static const int dx[] = {-1, 1, 0, 0};
  static const int dy[] = {0, 0, 1, -1};

  std::stack<BoardCoordinates> curr;
  curr.push(coordinates);
  while (!curr.empty()) {
    BoardCoordinates pos = curr.top();
    curr.pop();
    if (visited[pos.x][pos.y]) continue;
    visited[pos.x][pos.y] = true;

    for (int k = 0; k < 4; k++) {
      int x = pos.x + dx[k], y = pos.y + dy[k];
      if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) continue;
      if (getStoneAt(x, y) == Stone::None) {
        liberties++;
      } else if (getStoneAt(x, y) == getStoneAt(coordinates)) {
        curr.push(BoardCoordinates(x, y));
      }
    }

    component.push_back(pos);
  }

  return liberties;
}

void Board::removeStonesWithNoLiberties() {
  vector<vector<bool>> visited(boardSize, vector(boardSize, false));
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (visited[i][j]) continue;
      vector<BoardCoordinates> component;
      int liberties = countLibertiesAndGetComponent(visited, component, BoardCoordinates(i, j));
      if (liberties > 0) continue;

      for (const auto &coordinate : component) {
        removeStone(coordinate);
      }
    }
  }
}