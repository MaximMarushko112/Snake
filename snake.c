#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

void SetUp(enum Cells *field, const size_t size) {
    for (size_t i = 0; i < size; i++) {
        field[i]                     = Border;
        field[size * (size - 1) + i] = Border;
    }
    for (size_t i = 0; i < size * size; i += size) {
        field[i]            = Border;
        field[i + size - 1] = Border;
    }
    field[(size / 2) * (size + 1)] = Snake;
}

void Draw(enum Cells *field, const size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            switch (field[i * size + j]) {
                case Space:
                    printf(" ");
                    break;
                case Border:
                    printf("#");
                    break;
                case Apple:
                    printf("@");
                    break;
                case Snake:
                    printf("0");
                    break;
                default:
                    printf(" ");
                    break;
            }
        } 
        printf("\n\r");
    }
}

void NewApple(enum Cells *field, const size_t size, int *Applex, int *Appley) {
    field[*Appley * size + *Applex] = Space;
    
    *Applex = 1 + rand() % (size - 2);
    *Appley = 1 + rand() % (size - 2);
    
    field[*Appley * size + *Applex] = Apple;
}

void SnakeMove(enum Cells *field, const size_t size, int *Snakex, int *Snakey, enum Move *Snaked) {
    field[*Snakey * size + *Snakex] = Space;
    switch (*Snaked) {
        case Stop:
            break;
        case Left:
            *Snakex--;
            break;
        case Up:
            *Snakey++;
            break;
        case Right:
            *Snakex++;
            break;
        case Down:
            *Snakey--;
            break;
        default:
            break;
    }
    field[*Snakey * size + *Snakex] = Snake;
}

void Input(enum Move *Snaked) {
    initscr();
    char button = getch();
    endwin();
    switch (button) {
        case 'a':
            *Snaked = Left;
            break;
        case 'w':
            *Snaked = Up;
            break;
        case 'd':
            *Snaked = Right;
            break;
        case 's':
            *Snaked = Down;
            break;
        default:
            break;
    }
}