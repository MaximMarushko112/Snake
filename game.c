#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "snake.h"

int main() {
    initscr();
    const size_t size  = 20;
    enum Cells  *field = (enum Cells *) calloc(size * size, sizeof(char));
    assert(field != NULL);

    int       Applex = 1;
    int       Appley = 1;
    int       Snakex = size / 2;
    int       Snakey = size / 2;
    enum Move Snaked = Stop;
    
    srand(34);
    SetUp(field, size);
    Draw(field, size);
    NewApple(field, size, &Applex, &Appley);
    for (int i = 0; i < 10; i++) {
        Input(&Snaked);
        printw("%d\n\r", Snaked);
        SnakeMove(field, size, &Snakex, &Snakey, &Snaked);
        Draw(field, size);
        sleep(1);
    }
    free(field);
    endwin();
}