#include <stdio.h>
#include "board.h"
#include "game.h"
#include "player.h"

int main(){
    Board* b = sharedMemory();
    newBoard(b);

    Player players[4];
    for(int i = 0; i<4; i++){
        newPlayer(&players[i]);
        if(!players[i].pid) break;
    }

    if(!players[0].pid){

    }
    else if(!players[1].pid || !players[2].pid || !players[3].pid){

    }
    else{
        Game g;
        newGame(&g);


        munmap(b, sizeof(Board));
    }

    return 0;
}