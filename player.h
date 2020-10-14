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

typedef struct{
    pid_t pid;
    int to_player[2];
    int from_player[2];
}Player;

void newPlayer(Player* p);

Board* sharedMemory();


#endif