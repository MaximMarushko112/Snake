#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "snake.h"

int main() {
    const size_t size = 20;
    enum Cells *field = (enum Cells *) calloc(size * size, sizeof(char));
    assert(field != NULL);
    
    SetUp(field, size);
    Draw(field, size);
    /*for (int i = 0; i < 10; i++) {
        printf("\e[1;1H\e[2J");
        Draw(field, size);
        sleep(1);
    }*/

   free(field);
}