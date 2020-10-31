#include "game.h"

/*
 * Function: newGame
 * ----------------------------
 *   Inicia el juego y los turnos de los jugadores.
 *
 *   Game* g: Puntero al struct de juego que contiene
 *   el tablero, numero de turno, turnos y direccion en
 *   que avanzan los jugadores.
 *
 *   Returns: void, sin retorno.
 */
void newGame(Game* g){
    g->pass = 0;
    g->turn_number = 0;
    g->curr_turn = -1;
    g->turn_dir = 1;

    printf("\nEn que turno desea comenzar? (1, 2, 3 o 4)\n");
    printf("Su elección: ");
    int player_turn;
    scanf("%d", &player_turn);
    player_turn--;
    int i = 0;
    int j = 1;
    while(i < 4 && j < 4){
        if(i == player_turn) g->turns[i++] = 0;
        else g->turns[i++] = j++;
    }
    printf("+============================TURNOS=================================+\n");
    printf("1- Jugador %d\n2- Jugador %d\n3- Jugador %d\n4- Jugador %d\n", g->turns[0]+1,g->turns[1]+1,g->turns[2]+1,g->turns[3]+1);
    printf("+===================================================================+\n\n");
}

/*
 * Function: skipNextTurn
 * ----------------------------
 *   Permite saltar el siguiente turno.
 *
 *   Game* g: Puntero al struct de juego que contiene
 *   el tablero, numero de turno, turnos y direccion en
 *   que avanzan los jugadores.
 *
 *   Returns: void, sin retorno.
 */
void skipNextTurn(Game* g){
    g->pass = 1;
}

/*
 * Function: reverseTurns
 * ----------------------------
 *   Invierte la direccion de turnos de juego.
 *
 *   Game* g: Puntero al struct de juego que contiene
 *   el tablero, numero de turno, turnos y direccion en
 *   que avanzan los jugadores.
 *
 *   Returns: void, sin retorno.
 */
void reverseTurns(Game* g){
    g->turn_dir *= -1;

}

/*
 * Function: printTurn
 * ----------------------------
 *   Imprime el numero de turno. Ademas imprime la lista
 *   de jugadores, indicando a cual le corresponde el turno
 *   con la flecha ^.
 *
 *   Game* g: Puntero al struct de juego que contiene
 *   el tablero, numero de turno, turnos y direccion en
 *   que avanzan los jugadores.
 *
 *   Returns: void, sin retorno.
 */
void printTurn(Game* g){
    printf("Turno N°: %d\n", g->turn_number);
    printf("Jugadores: [%d, %d, %d, %d]", g->turns[0]+1, g->turns[1]+1, g->turns[2]+1, g->turns[3]+1);
    if(g->turn_dir == 1) printf(" -->\n");
    else  printf(" <--\n");
    printf("           ");
    for(int i = 0; i < 4; i++){
        if(i == g->curr_turn) printf(" ^ ");
        else printf("   ");
    }
    printf("\n");
}

/*
 * Function: nextTurn
 * ----------------------------
 *   Aumenta el numero de turno y cambia el turno actual.
 *   Además se revisa si este turno debe ser saltado o no.
 *
 *   Game* g: Puntero al struct de juego que contiene
 *   el tablero, numero de turno, turnos y direccion en
 *   que avanzan los jugadores.
 *
 *   Returns: int, jugador a quien corresponde el siguiente turno.
 */
int nextTurn(Game* g){
    g->curr_turn = (g->curr_turn+g->turn_dir+4)%4;
    g->turn_number++;
    if(g->pass){
        g->pass = 0;
        return nextTurn(g);
    }
    printTurn(g);
    return g->turns[g->curr_turn];
}