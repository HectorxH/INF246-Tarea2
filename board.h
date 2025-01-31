#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h> 
#include <stdlib.h>


#define START -1
#define FINISH 1
#define BONUS -2
#define SBONUS 2
#define NORMAL 0

/*
 * struct Board - el tablero
 * int dir - la dirección de tablero 
 * int pos[4] - arreglo con posiciones de cada jugador
 * int board[29] - celdas de tablero
*/
typedef struct{
    int dir;
    int pos[4];
    int board[29];
}Board;

void newBoard(Board* b);

void movePlayer(Board* b, int player_id, int roll);

int getCell(Board *b, int player_id);

int getPos(Board *b, int player_id);

void printRow(Board* b, int begin, int end, int inc, int align);

int SR(int player_id);

void printBoard(Board* b);

int SSR(int player_id);

int nextNormalPos(Board* b, int player_id); 

void teleportPlayer(Board* b, int player_id, int newpos);

int firstPlayer(Board* b);

int lastPlayer(Board* b);

int checkWinner(Board* b);

void reverseBoard(Board* b);

Board* sharedMemory();

#endif