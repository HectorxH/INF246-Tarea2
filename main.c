#include <stdio.h>
#include "board.h"
#include "game.h"
#include "player.h"

#define KILL -1
#define ROLL 1

int main(){
    Board* b = sharedMemory();
    newBoard(b);

    Player player[4];
    for(int i = 0; i<4; i++){
        newPlayer(&player[i], i);
        if(!player[i].pid) break;
    }

    int msg;

    if(!player[0].pid){
        Player p = player[0];
        int loop = 1;
        while(loop){
            read(p.to_player[READ], &msg, sizeof(int));
            if(msg == KILL) return 0;
            else if(msg == ROLL){
                int trash;
                scanf("%d", &trash);
                int roll = rand()%6+1;
                movePlayer(b, p.player_id, roll);
                write(p.from_player[WRITE], &msg, sizeof(int));
            }
        }

    }
    else if(!player[1].pid || !player[2].pid || !player[3].pid){

    }
    else{
        Game g;
        newGame(&g);
        printBoard(b);

        while(!checkWinner(b)){
            msg = ROLL;
            write(player[0].to_player[WRITE], &msg, sizeof(int));
            read(player[0].from_player[READ], &msg, sizeof(int));
            printBoard(b);
        }
        msg = KILL;
        write(player[0].to_player[WRITE], &msg, sizeof(int));


        munmap(b, sizeof(Board));
    }

    return 0;
}