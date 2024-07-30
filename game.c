#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "snake.h"

int main() {
    initscr();
    noecho();
    halfdelay(5);
    const size_t size  = 20;
    enum Cells  *field = (enum Cells *) calloc(size * size, sizeof(char));
    assert(field != NULL);

    struct Snake snake;
    struct Apple apple;
    
    srand(34);
    SetUp(field, size, &snake, &apple);
    Draw(field, size);
    for (int i = 0; i < 20; i++) {
        Input(&snake);
        SnakeMove(field, size, &snake, &apple);
        Draw(field, size);
    }
    free(field);
    endwin();
}