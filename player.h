#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "board.h"

#define READ 0
#define WRITE 1

/*
 * struct Player - el jugador
 * int player_id - id del jugador
 * pid_t pid - el pid de proceso correspondiente al jugador
 * int to_player[2] - pipe de hacia el jugador
 * int from_player[2] - pipe desde el jugador
*/
typedef struct{
    int player_id;
    pid_t pid;
    int to_player[2];
    int from_player[2];
}Player;

void newPlayer(Player* p, int player_id);

void sendToPlayer(Player* p, int* msg);

void readToPlayer(Player* p, int* msg);

void sendFromPlayer(Player* p, int* msg);

void readFromPlayer(Player* p, int* msg);

void killPlayer(Player* p);


#endif