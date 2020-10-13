#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "board.h"

int main(){

    Board* b = mmap(NULL, sizeof(Board), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    newBoard(b);
    printBoard(b);
    munmap(b, sizeof(Board));

    return 0;
}