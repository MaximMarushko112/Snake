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

void Draw (enum Cells *field, const size_t size);

void Input(enum Move *Snaked);

void NewApple(enum Cells *field, const size_t size, int *Applex, int *Appley);

void SetUp(enum Cells *field, const size_t size);

void SnakeMove(enum Cells *field, const size_t size, int *Snakex, int *Snakey, enum Move *Snaked);

#endif