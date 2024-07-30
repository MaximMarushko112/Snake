#ifndef SNAKE_H
#define SNAKE_H

enum Cells {
    Space,
    Border,
    Apple,
    Snake
};

enum Move {
    Stop,
    Left,
    Up,
    Right,
    Down
};

struct Snake {
    int Snakex;
    int Snakey;
    enum Move Snaked;
};

struct Apple {
    int Applex;
    int Appley;
};

void Draw     (enum Cells *field, const size_t size);

void Input    (struct Snake *snake);

void NewApple (enum Cells *field, const size_t size, struct Snake *snake, struct Apple *apple);

void SetUp    (enum Cells *field, const size_t size, struct Snake *snake, struct Apple *apple);

void SnakeMove(enum Cells *field, const size_t size, struct Snake *snake, struct Apple *apple);

void Eat      (enum Cells *field, const size_t size, struct Snake *snake, struct Apple *apple);

#endif