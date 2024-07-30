#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

void SetUp(enum Cells **field, const size_t size, struct Snake *snake, struct Apple *apple) {
    for (size_t i = 0; i < size; i++) {
        field[0][i]        = Border;
        field[size - 1][i] = Border;
        field[i][0]        = Border;
        field[i][size - 1] = Border;
    }

    NewApple(field, size, snake, apple);

    snake->x = size / 2;
    snake->y = size / 2;
    snake->d = Stop;
    field[snake->y][snake->x] = Snake;
}

void Draw(enum Cells **field, const size_t size) {
    move(0, 0);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            switch (field[i][j]) {
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

void NewApple(enum Cells **field, const size_t size, struct Snake *snake, struct Apple *apple) {
    apple->x = 1 + rand() % (size - 2);
    apple->y = 1 + rand() % (size - 2);
    
    while (apple->x == snake->x && apple->y == snake->y) {
        apple->x = 1 + rand() % (size - 2);
        apple->y = 1 + rand() % (size - 2);
    }
    
    field[apple->y][apple->x] = Apple;
}

void SnakeMove(enum Cells **field, const size_t size, struct Snake *snake, struct Apple *apple) {
    field[snake->y][snake->x] = Space;
    switch (snake->d) {
        case Stop:
            break;
        case Left:
            (snake->x)--;
            break;
        case Up:
            (snake->y)--;
            break;
        case Right:
            (snake->x)++;
            break;
        case Down:
            (snake->y)++;
            break;
        default:
            break;
    }

    Eat(field, size, snake, apple);

    field[snake->y][snake->x] = Snake;
}

void Input(struct Snake *snake) {
    char button = getch();
    switch (button) {
        case 'a':
            snake->d = Left;
            break;
        case 'w':
            snake->d = Up;
            break;
        case 'd':
            snake->d = Right;
            break;
        case 's':
            snake->d = Down;
            break;
        default:
            break;
    }
}

void Eat(enum Cells **field, const size_t size, struct Snake *snake, struct Apple *apple) {
    if (snake->x == apple->x && snake->y == apple->y) {
        NewApple(field, size, snake, apple);
    }
}