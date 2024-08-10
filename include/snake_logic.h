#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include <stdlib.h>
#include "data_types.h"

void BorderSetUp (struct Game *game);

void Eat         (struct Game *game, struct Snake *snake, struct Apple *apple);

void GameSetUp   (struct Game *game);

void NewApple    (struct Game *game, struct Snake *snake, struct Apple *apple);

void Overlay     (struct Game *game, struct Snake *snake, struct Apple *apple);

void SetUp       (struct Game *game, struct Snake *snake, struct Apple *apple);

void Settings    ();

void SnakeMove   (struct Game *game, struct Snake *snake, struct Apple *apple);

void SnakeSetUp  (struct Game *game, struct Snake *snake);

void SpaceSetUp  (struct Game *game);

#endif