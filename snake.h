#ifndef SNAKE_H
#define SNAKE_H

enum Status {
    Over,
    Going
};

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
    int x;
    int y;
    enum Move d;
};

struct Apple {
    int x;
    int y;
};

struct Game {
    enum Cells **field;
    size_t size;
    int score;
    enum Status status;
};

void Draw     (struct Game *game);

void Input    (struct Snake *snake);

void NewApple (struct Game *game, struct Snake *snake, struct Apple *apple);

void SetUp    (struct Game *game, struct Snake *snake, struct Apple *apple);

void SnakeMove(struct Game *game, struct Snake *snake, struct Apple *apple);

void Eat      (struct Game *game, struct Snake *snake, struct Apple *apple);

#endif