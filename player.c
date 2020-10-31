#include "player.h"

/*
 * Function: newPlayer
 * ----------------------------
 *   Incializa el nuevo jugador p de id player_id.
 *   Además, se crea el fork correspondiente.
 *
 *   Player* p - puntero al struct de jugador.
 *   int player_id: id de jugador
 *
 *   Returns: void, sin retorno.
 */
void newPlayer(Player* p, int player_id){
    pipe(p->to_player);
    pipe(p->from_player);

    p->pid = fork();
    p->player_id = player_id;

    if(p->pid == -1){
        printf("Error al realizar fork\n");
        exit(1);
    }

    if(p->pid == 0){
        close(p->to_player[WRITE]);
        close(p->from_player[READ]);
    }
    else{
        close(p->to_player[READ]);
        close(p->from_player[WRITE]);
    }
}

/*
 * Function: sendToPlayer
 * ----------------------------
 *   Envia el mensaje al jugador.
 *
 *   Player* p - puntero al struct de jugador.
 *   int* msg: el mensaje a enviar
 *
 *   Returns: void, sin retorno.
 */
void sendToPlayer(Player* p, int* msg){
    write(p->to_player[WRITE], msg, sizeof(int));
}

/*
 * Function: readToPlayer
 * ----------------------------
 *   Leer el mensaje enviado al jugador.
 *
 *   Player* p - puntero al struct de jugador.
 *   int* msg: el mensaje a leer
 *
 *   Returns: void, sin retorno.
 */
void readToPlayer(Player* p, int* msg){
    read(p->to_player[READ], msg, sizeof(int));
}

/*
 * Function: sendFromPlayer
 * ----------------------------
 *   Envia el mensaje al juego.
 *
 *   Player* p - puntero al struct de jugador.
 *   int* msg: el mensaje a enviar
 *
 *   Returns: void, sin retorno.
 */
void sendFromPlayer(Player* p, int* msg){
    write(p->from_player[WRITE], msg, sizeof(int));
}

/*
 * Function: readFromPlayer
 * ----------------------------
 *   Lee el mensaje enviado por el jugador.
 *
 *   Player* p - puntero al struct de jugador.
 *   int* msg: el mensaje a leer
 *
 *   Returns: void, sin retorno.
 */
void readFromPlayer(Player* p, int* msg){
    read(p->from_player[READ], msg, sizeof(int));
}

/*
 * Function: killPlayer
 * ----------------------------
 *   Cierra los pipes de jugador.
 *
 *   Player* p - puntero al struct de jugador.
 *
 *   Returns: void, sin retorno.
 */
void killPlayer(Player* p){
    if(p->pid == 0){
        close(p->to_player[READ]);
        close(p->from_player[WRITE]);
    }
    else{
        close(p->to_player[WRITE]);
        close(p->from_player[READ]);
    }
}
