#ifndef SNAKE_GRAPHICS_H
#define SNAKE_GRAPHICS_H

#include "snake_logic.h"

void ClearField (struct Game *game);

void DrawField  (struct Game *game);

void Drawxy     (struct Game *game, int x, int y, enum Cells cell);

void GameOver   (struct Game *game, struct Snake *snake);

void TheEnd     (struct Game *game, struct Snake *snake);

#endif