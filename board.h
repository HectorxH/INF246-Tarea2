#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define START -1
#define FINISH 1
#define BONUS -2
#define SBONUS 2

typedef struct{
    int dir;
    int pos[4];
    int board[29];
}Board;

void newBoard(Board* b);

void movePlayer(Board* b, int player_id, int roll);


int getPos(Board *b, int player_id);

void printRow(Board* b, int begin, int end, int inc, int align);

int SR(int player_id);

void printBoard(Board* b);

int SSR(int player_id);

int checkWinner(Board* b);

void reverseBoard(Board* b);

#endif