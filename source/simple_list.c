#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/simple_list.h"

struct List *CreateList() {
    struct List *new_list = (struct List *) calloc(1, sizeof(struct List));
    assert(new_list != NULL);

    new_list->size = 0;
    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
}

struct Node *CreateNode() {
    struct Node *new_node = (struct Node *) calloc(1, sizeof(struct Node));
    assert(new_node != NULL);
    
    return new_node;
}

struct List *FreeList(struct List *list) {
    assert(list != NULL);

    for (size_t i = 0; i < list->size; i++) 
        PopTail(list, NULL);
    
    free(list);

    return list;
}

struct Node *FreeNode(struct Node *node) {
    assert(node != NULL);

    const Data null_cell = {0, 0};

    node->data = null_cell;
    node->next = NULL;
    node->prev = NULL;
    
    free(node);

    return node;
}

void PopTail (struct List *list, Data *data) {
    assert(list != NULL);
    
    if (list->size != 0) {
        struct Node *tail = list->tail;
        if (data != NULL)
            *data = tail->data;

        list->tail = tail->prev;
        
        FreeNode(tail);
        if (list->tail != NULL)
            list->tail->next = NULL;
        else
            list->head = NULL;

        list->size--;
    }
}

void PushHead(struct List *list, Data *data) {
    assert(list != NULL);
    assert(data != NULL);

    struct Node *new_node = CreateNode();
    new_node->data = *data;
    new_node->next = list->head;
    if (list->size != 0)
        list->head->prev = new_node;

    list->head = new_node;
    if (list->tail == NULL) 
        list->tail = new_node;
    list->size++;
}