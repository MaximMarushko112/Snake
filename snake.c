#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake.h"

void SetUp(struct Game *game, struct Snake *snake, struct Apple *apple) {
    for (size_t i = 1; i < game->size - 1; i++) {
        for (size_t j = 1; j <= i; j++) {
            game->field[i][j] = Space;
            game->field[j][i] = Space;
        }
    }

    for (size_t i = 0; i < game->size; i++) {
        game->field[0][i]              = Border;
        game->field[game->size - 1][i] = Border;
        game->field[i][0]              = Border;
        game->field[i][game->size - 1] = Border;
    }

    snake->x = game->size / 2;
    snake->y = game->size / 2;
    snake->d = Stop;
    game->field[snake->y][snake->x] = Snake;

    NewApple(game, snake, apple);
}

void Draw(struct Game *game) {
    int winx, winy;
    getmaxyx(stdscr, winy, winx);

    if (game->status == Going) {
        for (size_t i = 0; i < game->size; i++) {
            move(winy/2 - game->size/2 + i, winx/2 - game->size/2);
            for (size_t j = 0; j < game->size; j++) {
                addch(game->field[i][j]);
            } 
        }
        mvprintw(winy/2 + game->size/2, winx/2 - game->size/2, "Score: %d", game->score);
    }
    else {
        char game_over[] = "GAME OVER!";
        mvprintw(winy/2, winx/2 - strlen(game_over)/2, "%s", game_over);
    }
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

    Overlay(game, snake, apple);
    
    if (game->status == Going) {
        game->field[snake->y][snake->x] = Snake;
    }
}

void Input(struct Snake *snake) {
    int button = getch();
    switch (button) {
        case KEY_LEFT:
        case 'a':
            snake->d = Left;
            break;
        case KEY_UP:
        case 'w':
            snake->d = Up;
            break;
        case KEY_RIGHT:
        case 'd':
            snake->d = Right;
            break;
        case KEY_DOWN:
        case 's':
            snake->d = Down;
            break;
        default:
            break;
    }
}

void Overlay(struct Game *game, struct Snake *snake, struct Apple *apple) {
    if (game->field[snake->y][snake->x] == Apple) {
        NewApple(game, snake, apple);
        game->score += 10;
        timeout(400 - game->score);
    }
    else if (game->field[snake->y][snake->x] == Border) {
        game->status = Over;
    }
}