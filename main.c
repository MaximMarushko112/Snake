#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "snake_graphics.h"
#include "snake_input.h"
#include "snake_logic.h"

int main() {
    struct Game game;
    struct Snake snake;
    struct Apple apple;
    
    SetUp(&game, &snake, &apple);
    while (game.status == Going) {
        Input(&snake);
        SnakeMove(&game, &snake, &apple);
    }
    GameOver(&game);
}