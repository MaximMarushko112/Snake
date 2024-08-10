#ifndef SIMPLE_LIST_H
#define SIMPLE_LIST_H

#include <stdlib.h>
#include "data_types.h"

struct List *CreateList();

struct Node *CreateNode();

struct List *FreeList(struct List *list);

struct Node *FreeNode(struct Node *node);

void         PopTail (struct List *list, Data *data);

void         PushHead(struct List *list, Data *data);
#endif