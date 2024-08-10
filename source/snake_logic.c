#include <assert.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "../include/simple_list.h"
#include "../include/snake_graphics.h"
#include "../include/snake_logic.h"

static const char score[] = "Score: ";
static const int MaxSpeed = 400;

void BorderSetUp(struct Game *game) {
    for (size_t i = 0; i < game->size; i++) {
        game->field[0][i]              = Border;
        game->field[game->size - 1][i] = Border;
        game->field[i][0]              = Border;
        game->field[i][game->size - 1] = Border;
    }
}

void Eat(struct Game *game, struct Snake *snake, struct Apple *apple) {
    NewApple(game, snake, apple);
            
    game->score += 10;
    mvprintw(game->win.row/2 + game->size/2, game->win.col/2 - game->size/2, "%s%d", score, game->score);
            
    timeout(MaxSpeed - game->score);
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

void NewApple(struct Game *game, struct Snake *snake, struct Apple *apple) {
    apple->cell.x = 1 + rand() % (game->size - 2);
    apple->cell.y = 1 + rand() % (game->size - 2);
    
    while (game->field[apple->cell.y][apple->cell.x] == Snake) {
        apple->cell.x = 1 + rand() % (game->size - 2);
        apple->cell.y = 1 + rand() % (game->size - 2);
    }
    
    Drawxy(game, apple->cell.x, apple->cell.y, Apple);
}

void Overlay(struct Game *game, struct Snake *snake, struct Apple *apple) {
    if (game->field[snake->body->head->data.y][snake->body->head->data.x] != Border &&
        game->field[snake->body->head->data.y][snake->body->head->data.x] != Snake) {
        Drawxy(game, snake->body->head->data.x, snake->body->head->data.y, Snake);
        
        if (game->field[apple->cell.y][apple->cell.x] == Snake) 
            Eat(game, snake, apple);
        else {
            Drawxy(game, snake->body->tail->data.x, snake->body->tail->data.y, Space);
            PopTail(snake->body, NULL);
        }
    }
    else {
        game->status = Over;
    }
}

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

void Settings() {
    noecho();
    timeout(MaxSpeed);
    keypad(stdscr, TRUE);
    srand(time(NULL));
}

void SnakeMove(struct Game *game, struct Snake *snake, struct Apple *apple) {
    struct Cell *new_head = (struct Cell *) calloc(1, sizeof(struct Cell));
    *new_head = snake->body->head->data;

    switch (snake->d) {
        case Stop:
            break;
        case Left:
            (new_head->x)--;
            break;
        case Up:
            (new_head->y)--;
            break;
        case Right:
            (new_head->x)++;
            break;
        case Down:
            (new_head->y)++;
            break;
        default:
            break;
    }

    if (snake->d != Stop) {
        PushHead(snake->body, new_head);

        Overlay(game, snake, apple);
    }
}

void SnakeSetUp (struct Game *game, struct Snake *snake) {
    snake->body = CreateList();
    struct Cell snake_start = {game->size / 2, game->size / 2};
    PushHead(snake->body, &snake_start);
    snake->d = Stop;
    game->field[snake->body->head->data.y][snake->body->head->data.x] = Snake;
}

void SpaceSetUp (struct Game *game) {
    for (size_t i = 1; i < game->size - 1; i++) {
        for (size_t j = 1; j <= i; j++) {
            game->field[i][j] = Space;
            game->field[j][i] = Space;
        }
    }
}