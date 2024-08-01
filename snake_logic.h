#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include <stdlib.h>

enum Status {
    Over,
    Going
};

enum Cells {
    Space  = ' ',
    Border = '#',
    Apple  = '@',
    Snake  = '0'
};

enum Move {
    Stop,
    Left,
    Up,
    Right,
    Down
};

struct Snake {
    int x;
    int y;
    enum Move d;
};

struct Apple {
    int x;
    int y;
};

struct Window {
    int row;
    int col;
};

struct Game {
    enum Cells  **field;
    size_t        size;
    int           score;
    enum Status   status;
    struct Window win;
};

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