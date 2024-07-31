#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "snake.h"

static const char game_over[] = "GAME OVER!";
static const char score[]     = "Score: ";
static const int  MaxSpeed    = 400;

void SetUp(struct Game *game, struct Snake *snake, struct Apple *apple) {
    initscr();
    Settings();
    GameSetUp(game);

    SpaceSetUp(game);
    BorderSetUp(game);
    SnakeSetUp(game, snake);
    NewApple(game, snake, apple);

    DrawField(game);
}

void DrawField(struct Game *game) {
    for (size_t i = 0; i < game->size; i++) {
        move(game->win.row/2 - game->size/2 + i, game->win.col/2 - game->size/2);
        for (size_t j = 0; j < game->size; j++) {
            addch(game->field[i][j]);
        } 
    }
    mvprintw(game->win.row/2 + game->size/2, game->win.col/2 - game->size/2, "%s%d", score, game->score);
}

void NewApple(struct Game *game, struct Snake *snake, struct Apple *apple) {
    apple->x = 1 + rand() % (game->size - 2);
    apple->y = 1 + rand() % (game->size - 2);
    
    while (game->field[apple->y][apple->x] == Snake) {
        apple->x = 1 + rand() % (game->size - 2);
        apple->y = 1 + rand() % (game->size - 2);
    }
    
    Drawxy(game, apple->x, apple->y, Apple);
}

void SnakeMove(struct Game *game, struct Snake *snake, struct Apple *apple) {
    Drawxy(game, snake->x, snake->y, Space);
    
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
    if (game->field[snake->y][snake->x] != Border) {
        Drawxy(game, snake->x, snake->y, Snake);
        
        if (game->field[apple->y][apple->x] == Snake) 
            Eat(game, snake, apple);
    }
    else {
        game->status = Over;
    }
}

void SpaceSetUp (struct Game *game) {
    for (size_t i = 1; i < game->size - 1; i++) {
        for (size_t j = 1; j <= i; j++) {
            game->field[i][j] = Space;
            game->field[j][i] = Space;
        }
    }
}

void BorderSetUp(struct Game *game) {
    for (size_t i = 0; i < game->size; i++) {
        game->field[0][i]              = Border;
        game->field[game->size - 1][i] = Border;
        game->field[i][0]              = Border;
        game->field[i][game->size - 1] = Border;
    }
}

void SnakeSetUp (struct Game *game, struct Snake *snake) {
    snake->x = game->size / 2;
    snake->y = game->size / 2;
    snake->d = Stop;
    
    game->field[snake->y][snake->x] = Snake;
}

void GameSetUp  (struct Game *game) {
    game->size   = 20;
    game->score  = 0;
    game->status = Going;
    
    game->field = (enum Cells **) calloc(game->size, sizeof(enum Cells *));
    assert(game->field != NULL);
    for (size_t i = 0; i < game->size; i++) {
        game->field[i] = calloc(game->size, sizeof(enum Cells));
        assert(game->field[i] != NULL);
    }
    
    getmaxyx(stdscr, game->win.row, game->win.col);
}

void Drawxy(struct Game *game, int x, int y, enum Cells cell) {
    assert(y < game->size && x < game->size);

    game->field[y][x] = cell;
    move(game->win.row/2 - game->size/2 + y, game->win.col/2 - game->size/2 + x);
    addch(game->field[y][x]);
}

void ClearField (struct Game *game) {
    for (size_t i = 0; i < game->size; i++) {
        for (size_t j = 0; j < game->size; j++) {
            game->field[i][j] = Space;
        }    
    }
}

void GameOver   (struct Game *game) {
    ClearField(game);
    DrawField (game);
    mvprintw(game->win.row/2 + game->size/2, game->win.col/2 - game->size/2, "               ");

    mvprintw(game->win.row/2,     game->win.col/2 - strlen(game_over)/2, "%s",   game_over);
    mvprintw(game->win.row/2 + 1, game->win.col/2 - strlen(game_over)/2, "%s%d", score, game->score);

    timeout(-1);
    getch();

    TheEnd(game);
}

void Settings() {
    noecho();
    timeout(MaxSpeed);
    keypad(stdscr, TRUE);
    srand(time(NULL));
}

void TheEnd (struct Game *game) {
    for (size_t i = 0; i < game->size; i++) {
        free(game->field[i]);
    }
    free(game->field);

    endwin();
}

void Eat(struct Game *game, struct Snake *snake, struct Apple *apple) {
    NewApple(game, snake, apple);
            
    game->score += 10;
    mvprintw(game->win.row/2 + game->size/2, game->win.col/2 - game->size/2, "%s%d", score, game->score);
            
    timeout(MaxSpeed - game->score);
}