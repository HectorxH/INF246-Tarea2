#include <stdio.h>
#include <time.h>
#include "board.h"
#include "game.h"
#include "player.h"

#define KILL -1

// Termino de turno
#define END_TURN 0
// Turno activo
#define ROLL 1
// Retroceder un paso
#define ONE_BACK 2
// Saltar el siguiente turno
#define SKIP_NEXT 3
// Invertir el orden de los turnos
#define REVERSE_TURNS 4
// Retroceder dos pasos
#define TWO_BACK 5
// Avanzar a la siguiente casilla blanca
#define NEXT_NORMAL 6
// Intercambiar los jugadores
#define SWAP 7
// Invertir el tablero
#define REVERSE_BOARD 8

/*
 * Function: d6
 * ----------------------------
 *   Rollea el dado d6.
 *
 *   Sin parametros.
 *
 *   Returns: int, valor del dado.
 */
int d6(){
    return rand()%6+1;
}

int main(){
    // Creación del tablero en memoria compartida
    Board* b = sharedMemory();
    newBoard(b);

    // Inicialización de los 4 jugadores
    Player player[4];
    int i;
    for(i = 0; i<4; i++){
        newPlayer(&player[i], i);
        if(!player[i].pid) break;
    }

    int msg;

    // La lógica de los jugadores
    if(!player[0].pid || !player[1].pid || !player[2].pid || !player[3].pid){
        Player p = player[i];
        srand(getpid());

        // A espera de mensaje
        while(1){
            readToPlayer(&p, &msg);
            if(msg == KILL){
                killPlayer(&p);
                return 0;
            }
            else if(msg == ROLL){
                int trash, aux_pos, effect;

                // Espera el input del jugador antes de continuar con el juego
                // El valor de trash no se utiliza para nada.
                printf("Ingrese cualquier número para continuar el juego (ej. 1): ");
                scanf("%d", &trash);
                printf("\n+===================================================================+\n\n");

                // Rollea el dado y avanza a los jugadores
                int roll = d6();
                movePlayer(b, p.player_id, roll);
                printBoard(b);

                // Revisión de efecto especial de la celda actual del jugador p.player_id
                aux_pos = getCell(b, p.player_id);

                // Caso de celda de tipo ?
                if(aux_pos == BONUS){

                    // effect retorna 0 o un número en rango [1...5]
                    // si effect == 0, el jugador eligió no activar el efecto ?
                    effect = SR(p.player_id);
                    if(effect){
                        //printf("El efecto elegido es: %d\n", effect);
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

                // Caso de celda de tipo ??
                else if(aux_pos == SBONUS){

                    // effect retorna 0 o un número en rango [1...5]
                    // si effect == 0, el jugador eligió no activar el efecto ??
                    effect = SSR(p.player_id);
                    if(effect){
                        //printf("El efecto elegido es: %d\n", effect);
                        int swap_player, swap_pos, curr_pos;
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
                                swap_player = lastPlayer(b);
                                swap_pos = getPos(b, swap_player);
                                curr_pos = getPos(b, p.player_id);
                                teleportPlayer(b, p.player_id, swap_pos);
                                msg = SWAP;
                                sendFromPlayer(&p, &msg);
                                msg = swap_player;
                                sendFromPlayer(&p, &msg);
                                msg = curr_pos;
                                sendFromPlayer(&p, &msg);
                                break;
                            case 4:
                                swap_player = firstPlayer(b);
                                swap_pos = getPos(b, swap_player);
                                curr_pos = getPos(b, p.player_id);
                                teleportPlayer(b, p.player_id, swap_pos);
                                msg = SWAP;
                                sendFromPlayer(&p, &msg);
                                msg = swap_player;
                                sendFromPlayer(&p, &msg);
                                msg = curr_pos;
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
                msg = END_TURN;
                sendFromPlayer(&p, &msg);
            }
            // Recepción de mensajes por otros jugadores

            // Mensaje: Retroceder un paso
            else if(msg == ONE_BACK){
                movePlayer(b, p.player_id, -1);
            }
            // Mensaje: Retroceder dos pasos
            else if(msg == TWO_BACK){
                movePlayer(b, p.player_id, -2);
            }

            // Mensaje: Avanzar a la siguiente casilla normal (blanca)
            else if(msg == NEXT_NORMAL){
                int normal_pos = nextNormalPos(b, p.player_id);
                teleportPlayer(b, p.player_id, normal_pos);
            }

            // Mensaje: Cambiar posiciones 
            else if(msg == SWAP){
                readToPlayer(&p, &msg);
                teleportPlayer(b, p.player_id, msg);
            }
        }
    }

    // Lógica de juego
    else{

        // Inicializar el juego
        Game g;
        newGame(&g);
        printBoard(b);

        // Mientras que no haya un ganador, continuamos el juego
        while(!checkWinner(b)){

            // Indicación al jugador actual que le toca
            msg = ROLL;
            int curr_player = nextTurn(&g);
            sendToPlayer(&player[curr_player], &msg);
            readFromPlayer(&player[curr_player], &msg);

            // Mientras no termine su turno
            while(msg != END_TURN){

                // Mensaje: avisa a los demás jugadores retroceder en 1 celda
                if(msg == ONE_BACK){
                    for(int i = 0; i < 4; i++){
                        if(i != curr_player) sendToPlayer(&player[i], &msg);
                    }
                }

                // Mensaje: salta el siguiente turno
                else if(msg == SKIP_NEXT){
                    skipNextTurn(&g);
                }

                // Mensaje: invierte el orden de turnos
                else if(msg == REVERSE_TURNS){
                    reverseTurns(&g);
                }

                // Mensaje: avisa a los demás jugadores retroceder en 2 celdas
                else if(msg == TWO_BACK){
                    for(int i = 0; i < 4; i++){
                        sendToPlayer(&player[i], &msg);
                    }
                }

                // Mensaje: avisa a los demás jugadores a avanzar a la siguiente celda blanca
                else if(msg == NEXT_NORMAL){
                    for(int i = 0; i < 4; i++){
                        if(i != curr_player) sendToPlayer(&player[i], &msg);
                    }
                }

                // Mensaje: Coordina el intercambio entre dos jugadores 
                else if(msg == SWAP){
                    readFromPlayer(&player[curr_player], &msg);
                    int target_player = msg;
                    msg = SWAP;
                    sendToPlayer(&player[target_player], &msg);
                    readFromPlayer(&player[curr_player], &msg);
                    sendToPlayer(&player[target_player], &msg);
                }

                // Mensaje: invierte el tablero
                else if(msg == REVERSE_BOARD){
                    reverseBoard(b);
                }
                readFromPlayer(&player[curr_player], &msg);
            }
        }

        // Finalización de los procesos de los 4 jugadores
        msg = KILL;
        sendToPlayer(&player[0], &msg);
        sendToPlayer(&player[1], &msg);
        sendToPlayer(&player[2], &msg);
        sendToPlayer(&player[3], &msg);
        for(int i = 0; i < 4; i++) killPlayer(&player[i]);

        printf("El ganador es el jugador %d!\n", checkWinner(b));
        // Liberación de memoria compartida
        munmap(b, sizeof(Board));
    }

    return 0;
}