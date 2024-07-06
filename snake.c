#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

void SetUp(enum Cells *field, const size_t size) {
    for (size_t i = 0; i < size; i++) {
        field[i]                     = Border;
        field[size * (size - 1) + i] = Border;
    }
    for (size_t i = 0; i < size * size; i += size) {
        field[i]            = Border;
        field[i + size - 1] = Border;
    }
}

void Draw(enum Cells *field, const size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            switch (field[i * size + j]) {
                case Space:
                    printf(" ");
                    break;
                case Border:
                    printf("#");
                    break;
                case Apple:
                    printf("@");
                    break;
                case Snake:
                    printf("0");
                    break;
                default:
                    printf(" ");
                    break;
            }
        } 
        printf("\n");
    }
}