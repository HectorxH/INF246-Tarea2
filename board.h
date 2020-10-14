#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdio.h>
#include <string.h>

#define BONUS 1
#define SBONUS 2
#define START 3
#define FINISH 4

typedef struct{
    int dir;
    int pos[4];
    int board[29];
}Board;

void newBoard(Board* b);

void movePlayer(Board* b, int player_id, int roll);

void printRow(Board* b, int begin, int end, int inc, int align);

void printBoard(Board* b);

int checkWinner(Board* b);

#endif