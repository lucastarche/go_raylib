#pragma once

const int boardSize = 19;
const int paddingAmount = 40;
const int tileSize = 40;
const int stoneRadius = 15;

// This -1 is because Go is played on the tile corners, rather than the insides
const int screenSize = (boardSize - 1) * tileSize + 2 * paddingAmount;

static_assert(boardSize > 0);
static_assert(paddingAmount >= 0);
static_assert(tileSize > 0);
static_assert(stoneRadius > 0);

enum class Stone {
  None, Black, White
};