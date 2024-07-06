#ifndef SNAKE_H
#define SNAKE_H

enum Cells {
    Space,
    Border,
    Apple,
    Snake
};

void SetUp(enum Cells *field, const size_t size);

void Draw (enum Cells *field, const size_t size);

#endif