#include <stdio.h>
#include<time.h>
#include "board.h"
#include "game.h"
#include "player.h"

#define KILL -1
#define ROLL 1

int d6(){
    return rand()%6+1;
}

int main(){
    Board* b = sharedMemory();
    newBoard(b);

    Player player[4];
    int i;
    for(i = 0; i<4; i++){
        newPlayer(&player[i], i);
        if(!player[i].pid) break;
    }

    int msg;

    if(!player[0].pid){
        Player p = player[i];
        srand(getpid());
        while(1){
            readToPlayer(&p, &msg);
            if(msg == KILL) return 0;
            else if(msg == ROLL){
                int trash;
                scanf("%d", &trash);
                int roll = d6();
                movePlayer(b, p.player_id, roll);
                sendFromPlayer(&p, &msg);
            }
        }

    }
    else if(!player[1].pid || !player[2].pid || !player[3].pid){
        Player p = player[i];
        srand(getpid());
        while(1){
            readToPlayer(&p, &msg);
            if(msg == KILL) return 0;
            else if(msg == ROLL){
                int trash;
                scanf("%d", &trash);
                int roll = d6();
                movePlayer(b, p.player_id, roll);
                sendFromPlayer(&p, &msg);
            }
        }
    }
    else{
        Game g;
        newGame(&g);
        printBoard(b);

        while(!checkWinner(b)){
            msg = ROLL;
            int curr_player = nextTurn(&g);

            sendToPlayer(&player[curr_player], &msg);
            readFromPlayer(&player[curr_player], &msg);
            printBoard(b);
        }
        msg = KILL;
        sendToPlayer(&player[0], &msg);
        sendToPlayer(&player[1], &msg);
        sendToPlayer(&player[2], &msg);
        sendToPlayer(&player[3], &msg);

        printf("El ganador es el jugador %d!\n", checkWinner(b));

        munmap(b, sizeof(Board));
    }

    return 0;
}