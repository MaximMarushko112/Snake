#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "snake.h"

int main() {
    initscr();

    struct Game game;
    struct Snake snake;
    struct Apple apple;
    
    SetUp(&game, &snake, &apple);
    while (game.status == Going) {
        Input(&snake);
        SnakeMove(&game, &snake, &apple);
    }
    GameOver(&game);
    endwin();
}