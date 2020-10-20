#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <string.h>
#include "board.h"

typedef struct{
    Board* board;
    int pass;
    int turn_number;
    int turns[4];
    int curr_turn;
}Game;

void newGame(Game* g);

void skipNextTurn(Game* g);

void reverseTurns(Game* g);

int nextTurn(Game* g);

#endif