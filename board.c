#include "board.h"

void newBoard(Board* b){
    b->dir = 1;
    for(int i = 0; i < 29; i++) b->board[i] = NORMAL;

    b->board[0] = START;
    b->board[28] = FINISH;

    b->board[2] = BONUS;
    b->board[4] = BONUS;
    b->board[6] = BONUS;
    b->board[12] = BONUS;
    b->board[14] = BONUS;
    b->board[21] = BONUS;
    b->board[23] = BONUS;
    b->board[25] = BONUS;
    b->board[27] = BONUS;

    b->board[16] = SBONUS;
    b->board[22] = SBONUS;
    b->board[24] = SBONUS;
    b->board[26] = SBONUS;

    for(int i=0; i<4; i++) b->pos[i] = 0;
}


int getCell(Board *b, int player_id){
    return b->board[b->pos[player_id]];
}

int getPos(Board *b, int player_id){
    return b->pos[player_id];
}

int SR(int player_id){
    int seleccion;
    if(!player_id){
        int efecto;
        printf("Quiere activar el efecto '\?'.\nIngrese 1 para activar el efecto, en otro caso ingrese un 0\n");
        scanf("%d", &efecto);
        if(!efecto){
           return 0;
        }
    }
    seleccion = rand()%5+1;
    switch(seleccion){
        case 1:
            printf("Efecto ocurrido: Woosh! El jugador retrocede una cuadricula.\n");
            break;
        case 2:
            printf("Efecto ocurrido: Woosh! Los demas jugadores retroceden una cuadricula.\n");
            break;
        case 3:
            printf("Efecto ocurrido: Yay! Puedes avanzar una cuadricula.\n");
            break;
        case 4:
            printf("Efecto ocurrido: El siguiente jugador no puede avanzar.\n");
            break;
        case 5:
            printf("Efecto ocurrido: Cambio en el sentido de los turnos.\n");
            break;
    }

    return seleccion;
}

int SSR(int player_id){
    int seleccion;
    if(!player_id){
        int efecto;
        printf("Quiere activar el efecto '\?\?'.\nIngrese 1 para activar el efecto, en otro caso ingrese un 0\n");
        scanf("%d", &efecto);
        if(!efecto){
           return 0;
        }
    }
    seleccion = rand()%101;
    if(seleccion < 10){
        printf("Efecto ocurrido: Cambio en el sentido del tablero!\n");
        return 5;
    }
    else if(seleccion < 30){
        printf("Efecto ocurrido: Efecto ocurrido: El jugador cambia de posicion con el jugador que va en primer lugar!\n");
        return 4;
    }
    else if(seleccion < 50){
        printf("Efecto ocurrido: Woosh! Los demas jugadores avanzan hasta su proxima cuadricula blanca!\n");
        return 2;
    }
    else if(seleccion < 70){
        printf("Efecto ocurrido: Hm. El jugador cambia de posicion con el jugador que va en ultimo lugar!\n");
        return 3;
    }
    else{
        printf("Efecto ocurrido: Todos los jugadores retroceden 2 cuadriculas!\n");
        return 1;
    }
    return seleccion;
}

int nextNormalPos(Board* b, int player_id){
    // Direccion start->finish
    int i;
    if(b->dir == 1){
        for(i = getPos(b, player_id); i < 28; i++){
            if(b->board[i] == NORMAL){
                return i;
            }
        }

    }
    // Direccion finish->start
    else{
        for(i = getPos(b, player_id); i > 0; i--){
            if(b->board[i] == NORMAL){
                return i;
            }
        }
    }
    // No hay mas casillas blancas, sin efecto.
    return getPos(b, player_id);
}

void teleportPlayer(Board* b, int player_id, int newpos){
    b->pos[player_id] = newpos;
}

int firstPlayer(Board* b){
    int search, player;
    // Direccion start->finish
    // El "primero" va a tener la casilla con numero mas grande
    if(b->dir == 1){
        search = -1;
        for(int i = 0; i < 4; i++){
            if(b->pos[i] > search){
                player = i;
                search = b->pos[i];
            }
        }
    }
    // Direccion finish->start
    // El "primero" va a tener la casilla con numero mas chico
    else{
        search = 29;
        for(int i = 0; i < 4; i++){
            if(b->pos[i] < search){
                player = i;
                search = b->pos[i];
            }
        }
    }
    return player;
}

int lastPlayer(Board* b){
    int search, player;
     // Direccion start->finish
     // El "ultimo" va a tener la casilla con numero mas chica
    if(b->dir == 1){
        search = 29;
        for(int i = 0; i < 4; i++){
            if(b->pos[i] < search){
                player = i;
                search = b->pos[i];
            }
        }
    }
    // Direccion finish->start
    // El "ultimo" va a tener la casilla con numero mas grande
    else{
        search = -1;
        for(int i = 0; i < 4; i++){
            if(b->pos[i] > search){
                player = i;
                search = b->pos[i];
            }
        }
    }
    return player;
}

void movePlayer(Board* b, int player_id, int roll){
    b->pos[player_id] += roll*b->dir;
    if(b->pos[player_id] > 28) b->pos[player_id] = 28;
    if(b->pos[player_id] < 0) b->pos[player_id] = 0;
}

void printRow(Board* b, int begin, int end, int inc, int align){
    if(align) for(int i = 0; i < 8; i++) printf("      ");
    for(int i = begin; i*inc < end*inc; i+=inc) printf("┌────┐");
    printf("\n");

    if(align) for(int i = 0; i < 8; i++) printf("      ");
    for(int i = begin; i*inc < end*inc; i+=inc){
        char content[6];
        if(b->board[i] == BONUS) strcpy(content, " ?  ");
        else if(b->board[i] == SBONUS) strcpy(content, " ?? ");
        else if(b->board[i] == START) strcpy(content, "sta ");
        else if(b->board[i] == FINISH) strcpy(content, "end ");
        else strcpy(content, "    ");

        printf("│%s│", content);
    }
    printf("\n");

    if(align) for(int i = 0; i < 8; i++) printf("      ");
    for(int i = begin; i*inc < end*inc; i+=inc){
        printf("|");

        if( b->pos[0] == i) printf("1");
        else printf(" ");

        if( b->pos[1] == i) printf("2");
        else printf(" ");

        if( b->pos[2] == i) printf("3");
        else printf(" ");

        if( b->pos[3] == i) printf("4");
        else printf(" ");

        printf("|");
    }
    printf("\n");
 
    if(align) for(int i = 0; i < 8; i++) printf("      ");
    for(int i = begin; i*inc < end*inc; i+=inc) printf("└────┘");
    printf("\n");
}


void printBoard(Board* b){
   printRow(b, 20, 29, 1, 0);
   printRow(b, 19, 20, 1, 0);
   printRow(b, 18, 9, -1, 0);
   printRow(b, 9, 10, 1, 1);
   printRow(b, 0, 9, 1, 0);
}

int checkWinner(Board*b){
    int goal = (b->dir>0)?28:0;

    if(b->pos[0] == goal) return 1;
    else if(b->pos[1] == goal) return 2;
    else if(b->pos[2] == goal) return 3;
    else if(b->pos[3] == goal) return 4;
    else return 0;
}

void reverseBoard(Board* b){
    b->dir *= -1;
    for(int i = 0; i<29; i++) b->board[i] *= -1;
}


