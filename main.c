#include <stdio.h>
#include <time.h>
#include "board.h"
#include "game.h"
#include "player.h"

#define KILL -1
#define END_TURN 0
#define ROLL 1
#define ONE_BACK 2
#define SKIP_NEXT 3
#define REVERSE_TURNS 4

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

    if(!player[0].pid || !player[1].pid || !player[2].pid || !player[3].pid){
        Player p = player[i];
        srand(getpid());
        while(1){
            readToPlayer(&p, &msg);
            if(msg == KILL){
                killPlayer(&p);
                return 0;
            }
            else if(msg == ROLL){
                int trash, aux_pos, effect;
                scanf("%d", &trash);
                int roll = d6();
                movePlayer(b, p.player_id, roll);
                printBoard(b);
                aux_pos = getPos(b, p.player_id);

                if(aux_pos == BONUS){
                    effect = SR(p.player_id);
                    if(effect){
                        printf("El efecto elegido es: %d\n", effect);
                        switch(effect){
                            case 1:
                                movePlayer(b, p.player_id, -1);
                                break;
                            case 2:
                                msg = ONE_BACK;
                                sendFromPlayer(&p, &msg);
                                break;
                            case 3:
                                movePlayer(b, p.player_id, 1);
                                break;
                            case 4:
                                msg = SKIP_NEXT;
                                sendFromPlayer(&p, &msg);
                                break;
                            case 5:
                                msg = REVERSE_TURNS;
                                sendFromPlayer(&p, &msg);
                                break;
                        }
                    }
                    else{
                        printf("Se ha eligido no activar el efecto!\n");
                    }
                }
                else if(aux_pos == SBONUS){
                    effect = SSR(p.player_id);
                    if(effect){
                        printf("El efecto elegido es: %d\n", effect);
                    }
                    else{
                        printf("Se ha eligido no activar el efecto!\n");
                    }
                }
                msg = END_TURN;
                sendFromPlayer(&p, &msg);
            }
            else if(msg == ONE_BACK){
                movePlayer(b, p.player_id, -1);
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
            while(msg != END_TURN){
                if(msg == ONE_BACK){
                    for(int i = 0; i < 4; i++){
                        if(i != curr_player) sendToPlayer(&player[i], &msg);
                    }
                }
                else if(msg == SKIP_NEXT){
                    skipNextTurn(&g);
                }
                else if(msg == REVERSE_TURNS){
                    reverseTurns(&g);
                }
                readFromPlayer(&player[curr_player], &msg);
            }
        }
        msg = KILL;
        sendToPlayer(&player[0], &msg);
        sendToPlayer(&player[1], &msg);
        sendToPlayer(&player[2], &msg);
        sendToPlayer(&player[3], &msg);
        for(int i = 0; i < 4; i++) killPlayer(&player[i]);

        printf("El ganador es el jugador %d!\n", checkWinner(b));

        munmap(b, sizeof(Board));
    }

    return 0;
}