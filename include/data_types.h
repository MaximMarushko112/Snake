#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdlib.h>
#include "enums.h"

struct Cell {
    int x;
    int y;
};

typedef struct Cell Data;

struct Snake {
    struct List *body;
    enum Move d;
};

struct Apple {
    struct Cell cell;
};

struct Window {
    int row;
    int col;
};

struct Game {
    enum Cells  **field;
    size_t        size;
    int           delay;
    int           score;
    enum Status   status;
    struct Window win;
};

struct Node {
    Data         data;
    struct Node *prev;
    struct Node *next;
};

struct List {
    size_t       size;
    struct Node *head;
    struct Node *tail;
};

#endif