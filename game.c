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

    int       Applex = 1;
    int       Appley = 1;
    int       Snakex = 10;
    int       Snakey = 10;
    enum Move Snaked = Stop;
    
    srand(34);
    SetUp(field, size);
    NewApple(field, size, &Applex, &Appley);
    Draw(field, size);
    for (int i = 0; i < 10; i++) {
        Input(&Snaked);
        SnakeMove(field, size, &Snakex, &Snakey, &Snaked);
        Draw(field, size);
    }
    free(field);
    endwin();
}