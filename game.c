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
    enum Cells  **field = (enum Cells **) calloc(size, sizeof(enum Cells *));
    assert(field != NULL);
    for (size_t i = 0; i < size; i++) {
        field[i] = calloc(size, sizeof(char));
        assert(field[i] != NULL);
    }

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

    for (size_t i = 0; i < size; i++) {
        free(field[i]);
    }
    free(field);
    endwin();
}