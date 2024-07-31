#ifndef SNAKE_H
#define SNAKE_H

enum Status {
    Over,
    Going
};

enum Cells {
    Space  = ' ',
    Border = '#',
    Apple  = '@',
    Snake  = '0'
};

enum Move {
    Stop,
    Left,
    Up,
    Right,
    Down
};

struct Snake {
    int x;
    int y;
    enum Move d;
};

struct Apple {
    int x;
    int y;
};

struct Window {
    int row;
    int col;
};
struct Game {
    enum Cells  **field;
    size_t        size;
    int           score;
    enum Status   status;
    struct Window win;
};

void BorderSetUp(struct Game *game);

void ClearField (struct Game *game);

void DrawField  (struct Game *game);

void Drawxy     (struct Game *game, int x, int y, enum Cells cell);

void Eat        (struct Game *game, struct Snake *snake, struct Apple *apple);

void GameOver   (struct Game *game);

void GameSetUp  (struct Game *game);

void Input      (struct Snake *snake);

void NewApple   (struct Game *game, struct Snake *snake, struct Apple *apple);

void Overlay    (struct Game *game, struct Snake *snake, struct Apple *apple);

void SetUp      (struct Game *game, struct Snake *snake, struct Apple *apple);

void Settings   ();

void SnakeMove  (struct Game *game, struct Snake *snake, struct Apple *apple);

void SnakeSetUp (struct Game *game, struct Snake *snake);

void SpaceSetUp (struct Game *game);

void TheEnd     (struct Game *game);

#endif