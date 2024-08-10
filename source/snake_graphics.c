#include <assert.h>
#include <ncurses.h>
#include <string.h>
#include "../include/simple_list.h"
#include "../include/snake_graphics.h"
#include "../include/snake_logic.h"

static const char game_over[] = "GAME OVER!";
static const char score[] = "Score: ";

void ClearField (struct Game *game) {
    for (size_t i = 0; i < game->size; i++) {
        for (size_t j = 0; j < game->size; j++) {
            game->field[i][j] = Space;
        }    
    }
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

void Drawxy(struct Game *game, int x, int y, enum Cells cell) {
    assert(y < game->size && x < game->size);

    game->field[y][x] = cell;
    move(game->win.row/2 - game->size/2 + y, game->win.col/2 - game->size/2 + x);
    addch(game->field[y][x]);
}

void GameOver(struct Game *game, struct Snake *snake) {
    ClearField(game);
    DrawField (game);
    mvprintw(game->win.row/2 + game->size/2, game->win.col/2 - game->size/2, "               ");

    mvprintw(game->win.row/2,     game->win.col/2 - strlen(game_over)/2, "%s",   game_over);
    mvprintw(game->win.row/2 + 1, game->win.col/2 - strlen(game_over)/2, "%s%d", score, game->score);

    timeout(-1);
    getch();

    TheEnd(game, snake);
}

void TheEnd (struct Game *game, struct Snake *snake) {
    for (size_t i = 0; i < game->size; i++) {
        free(game->field[i]);
    }
    free(game->field);

    FreeList(snake->body);

    endwin();
}