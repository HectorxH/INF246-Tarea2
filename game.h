#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <string.h>
#include "board.h"

/*
 * struct Game - el juego
 * int pass - indica si se debe saltar el siguiente turno (0 o 1)
 * int turn_number - el número de turno
 * int turns[4] - arreglo de jugadores en orden de turnos
 * int curr_turn - turno actual
 * int turn_dir - la dirección de turno
*/
typedef struct{
    Board* board;
    int pass;
    int turn_number;
    int turns[4];
    int curr_turn;
    int turn_dir;
}Game;

void newGame(Game* g);

void skipNextTurn(Game* g);

void reverseTurns(Game* g);

void printTurn(Game* g);

int nextTurn(Game* g);

#endif