#include <ncurses.h>
#include "snake_input.h"
#include "snake_logic.h"

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