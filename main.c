#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "snake.h"

int main() {
    initscr();
    noecho();
    timeout(400);
    keypad(stdscr, TRUE);
    srand(time(NULL));

    struct Game game;
    game.size = 20;
    game.field = (enum Cells **) calloc(game.size, sizeof(enum Cells *));
    assert(game.field != NULL);
    for (size_t i = 0; i < game.size; i++) {
        game.field[i] = calloc(game.size, sizeof(enum Cells));
        assert(game.field[i] != NULL);
    }
    game.score = 0;
    game.status = Going;

    struct Snake snake;
    struct Apple apple;
    
    SetUp(&game, &snake, &apple);
    Draw(&game);
    while (game.status == Going) {
        Input(&snake);
        SnakeMove(&game, &snake, &apple);
        Draw(&game);
    }
    timeout(-1);
    getch();

    for (size_t i = 0; i < game.size; i++) {
        free(game.field[i]);
    }
    free(game.field);
    endwin();
}