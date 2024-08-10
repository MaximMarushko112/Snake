#ifndef ENUMS_H
#define ENUMS_H

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

#endif