#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

void SetUp(enum Cells *field, const size_t size, struct Snake *snake, struct Apple *apple) {
    for (size_t i = 0; i < size; i++) {
        field[i]                     = Border;
        field[size * (size - 1) + i] = Border;
    }
    for (size_t i = 0; i < size * size; i += size) {
        field[i]            = Border;
        field[i + size - 1] = Border;
    }

    NewApple(field, size, snake, apple);

    snake->Snakex = size / 2;
    snake->Snakey = size / 2;
    snake->Snaked = Stop;
    field[snake->Snakey * size + snake->Snakey] = Snake;
}

void Draw(enum Cells *field, const size_t size) {
    move(0, 0);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            switch (field[i * size + j]) {
                case Space:
                    addch(' ');
                    break;
                case Border:
                    addch('#');
                    break;
                case Apple:
                    addch('@');
                    break;
                case Snake:
                    addch('0');
                    break;
                default:
                    addch(' ');
                    break;
            }
        } 
        printw("\n\r");
    }
}

void NewApple(enum Cells *field, const size_t size, struct Snake *snake, struct Apple *apple) {
    apple->Applex = 1 + rand() % (size - 2);
    apple->Appley = 1 + rand() % (size - 2);
    
    while (apple->Applex == snake->Snakex && apple->Appley == snake->Snakey) {
        apple->Applex = 1 + rand() % (size - 2);
        apple->Appley = 1 + rand() % (size - 2);
    }
    
    field[apple->Appley * size + apple->Applex] = Apple;
}

void SnakeMove(enum Cells *field, const size_t size, struct Snake *snake, struct Apple *apple) {
    field[(snake->Snakey) * size + (snake->Snakex)] = Space;
    switch (snake->Snaked) {
        case Stop:
            break;
        case Left:
            (snake->Snakex)--;
            break;
        case Up:
            (snake->Snakey)--;
            break;
        case Right:
            (snake->Snakex)++;
            break;
        case Down:
            (snake->Snakey)++;
            break;
        default:
            break;
    }

    Eat(field, size, snake, apple);

    field[snake->Snakey * size + snake->Snakex] = Snake;
}

void Input(struct Snake *snake) {
    char button = getch();
    switch (button) {
        case 'a':
            snake->Snaked = Left;
            break;
        case 'w':
            snake->Snaked = Up;
            break;
        case 'd':
            snake->Snaked = Right;
            break;
        case 's':
            snake->Snaked = Down;
            break;
        default:
            break;
    }
}

void Eat(enum Cells *field, const size_t size, struct Snake *snake, struct Apple *apple) {
    if (snake->Snakex == apple->Applex && snake->Snakey == apple->Appley) {
        NewApple(field, size, snake, apple);
    }
}