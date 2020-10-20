#include "game.h"

void newGame(Game* g){
    g->pass = 0;
    g->turn_number = 0;
    g->curr_turn = -1;


    printf("En que turno desea comenzar? (1, 2, 3 o 4)\n");
    printf("Turno: ");
    int player_turn;
    scanf("%d", &player_turn);
    player_turn--;
    int i = 0;
    int j = 1;
    while(i < 4 && j < 4){
        if(i == player_turn) g->turns[i++] = 0;
        else g->turns[i++] = j++;
    }

    printf("Los turnos seran:\n1- Jugador %d\n2- Jugador %d\n3- Jugador %d\n4- Jugador %d\n", g->turns[0]+1,g->turns[1]+1,g->turns[2]+1,g->turns[3]+1);
}

void skipNextTurn(Game* g){
    g->pass = 1;
}

void reverseTurns(Game* g){
    int temp = g->turns[0];
    g->turns[0] = g->turns[3];
    g->turns[3] = temp;

    temp = g->turns[1];
    g->turns[1] = g->turns[2];
    g->turns[2] = temp;

    g->curr_turn = 3-g->curr_turn;
}

void printTurn(Game* g){
    printf("Turno N°: %d\n", g->turn_number);
}

int nextTurn(Game* g){
    g->curr_turn = (g->curr_turn+1)%4;
    g->turn_number++;
    if(g->pass){
        g->pass = 0;
        return nextTurn(g);
    }
    printTurn(g);
    return g->turns[g->curr_turn];
}