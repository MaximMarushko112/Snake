#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

void SetUp(struct Game *game, struct Snake *snake, struct Apple *apple) {
    for (size_t i = 0; i < game->size; i++) {
        game->field[0][i]              = Border;
        game->field[game->size - 1][i] = Border;
        game->field[i][0]              = Border;
        game->field[i][game->size - 1] = Border;
    }

    NewApple(game, snake, apple);

    snake->x = game->size / 2;
    snake->y = game->size / 2;
    snake->d = Stop;
    game->field[snake->y][snake->x] = Snake;
}

void Draw(struct Game *game) {
    move(0, 0);
    for (size_t i = 0; i < game->size; i++) {
        for (size_t j = 0; j < game->size; j++) {
            switch (game->field[i][j]) {
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
    printw("Score: %d", game->score);
}

void NewApple(struct Game *game, struct Snake *snake, struct Apple *apple) {
    apple->x = 1 + rand() % (game->size - 2);
    apple->y = 1 + rand() % (game->size - 2);
    
    while (apple->x == snake->x && apple->y == snake->y) {
        apple->x = 1 + rand() % (game->size - 2);
        apple->y = 1 + rand() % (game->size - 2);
    }
    
    game->field[apple->y][apple->x] = Apple;
}

void SnakeMove(struct Game *game, struct Snake *snake, struct Apple *apple) {
    game->field[snake->y][snake->x] = Space;
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

    Eat(game, snake, apple);

    game->field[snake->y][snake->x] = Snake;
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

void Eat(struct Game *game, struct Snake *snake, struct Apple *apple) {
    if (game->field[snake->y][snake->x] == Apple) {
        NewApple(game, snake, apple);
        game->score += 10;
    }
}