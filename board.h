#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdio.h>
#include <string.h>

#define BONUS -1
#define SBONUS -2
#define START -3
#define FINISH -4

typedef struct{
    int dir;
    int players[4];
    int board[29];
}Board;

void newBoard(Board* b);

void printRow(Board* b, int begin, int end, int inc, int align);

void printBoard(Board* b);

#endif