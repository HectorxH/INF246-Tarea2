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
#define TWO_BACK 5
#define NEXT_NORMAL 6
#define SWAP 7
#define REVERSE_BOARD 8

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
                                msg = REVERSE_BOARD;
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
                        switch(effect){
                            case 1:
                                msg = TWO_BACK;
                                sendFromPlayer(&p, &msg);
                                break;
                            case 2:
                                msg = NEXT_NORMAL;
                                sendFromPlayer(&p, &msg);
                                break;
                            case 3:
                                int last_player = lastPlayer(b);
                                int last_pos = getPos(b, last_player);
                                int curr_pos = getPos(b, p.player_id);
                                teleportPlayer(b, p.player_id, last_pos);
                                msg = SWAP;
                                sendFromPlayer(&p, &msg);
                                msg = last_player;
                                sendFromPlayer(&p, &msg);
                                msg = curr_pos;
                                sendFromPlayer(&p, &msg);
                                break;
                            case 4:
                                int first_player = lastPlayer(b);
                                int first_pos = getPos(b, last_player);
                                int curr_pos = getPos(b, p.player_id);
                                teleportPlayer(b, p.player_id, first_pos);
                                msg = SWAP;
                                sendFromPlayer(&p, &msg);
                                msg = last_player;
                                sendFromPlayer(&p, &msg);
                                msg = curr_pos;
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
                msg = END_TURN;
                sendFromPlayer(&p, &msg);
            }
            else if(msg == ONE_BACK){
                movePlayer(b, p.player_id, -1);
            }
            else if(msg == TWO_BACK){
                movePlayer(b, p.player_id, -2);
            }
            else if(msg == NEXT_NORMAL){
                int normal_pos = nextNormalPos(b, p.player_id);
                teleportPlayer(b, p.player_id, normal_pos);
            }
            else if(msg == SWAP){
                readToPlayer(&p, &msg);
                teleportPlayer(b, p.player_id, msg);
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
                else if(msg == TWO_BACK){
                    for(int i = 0; i < 4; i++){
                        sendToPlayer(&player[i], &msg);
                    }
                }
                else if(msg == NEXT_NORMAL){
                    for(int i = 0; i < 4; i++){
                        if(i != curr_player) sendToPlayer(&player[i], &msg);
                    }
                }
                else if(msg == SWAP){
                    readFromPlayer(&player[curr_player], &msg);
                    int target_player = msg;
                    msg = SWAP;
                    sendToPlayer(&player[target_player], &msg);
                    readFromPlayer(&player[curr_player], &msg);
                    sendToPlayer(&player[target_player], &msg);
                }
                else if(msg == REVERSE_BOARD){
                    reverseBoard(b);
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