#include <ncurses.h>
#include "../include/snake_input.h"
#include "../include/snake_logic.h"

void Input(struct Game *game, struct Snake *snake) {
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
        case 'p':
            Pause(game);
            break;
        default:
            break;
    }
}

void Pause(struct Game *game) {
    timeout(-1);
    int button = 0;
    while ((button = getch()) != 'p') {

    }
    timeout(game->delay);
}