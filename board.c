#include "board.h"

/*
 * Function: newBoard
 * ----------------------------
 *   Función que inicia el tablero marcando las celdas especiales.
 *   START = 1, FINISH = -1, BONUS (?) = -2, SBONUS (??) = 2, NORMAL = 0.
 *
 *   Board* b: Puntero al struct de tablero.
 *
 *   Returns: void, sin retorno.
 */
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

/*
 * Function: getCell
 * ----------------------------
 *   Función get para tipo de la celda en que está jugador player_id.
 *
 *   Board* b: Puntero al struct de tablero.
 *   int player_id: id de jugador
 *
 *   Returns: int, tipo de celda de jugador indicado.
 */
int getCell(Board *b, int player_id){
    return b->board[b->pos[player_id]];
}

/*
 * Function: getPos
 * ----------------------------
 *   Función get para la posición del jugador player_id.
 *
 *   Board* b: Puntero al struct de tablero.
 *   int player_id: id de jugador
 *
 *   Returns: int, posición de jugador indicado.
 */
int getPos(Board *b, int player_id){
    return b->pos[player_id];
}

/*
 * Function: SR
 * ----------------------------
 *   Función de activación de efecto tipo ?
 *
 *   int player_id: id de jugador
 *
 *   Returns: int, 0 en caso de no activar el efecto, el efecto en rango [1...5] etoc.
 */
int SR(int player_id){
    int seleccion;
    printf("\n+==========================CELDA=ESPECIAL===========================+\n");
    if(!player_id){
        int efecto;
        printf("Quiere activar el efecto '\?'.\nIngrese 1 para activar el efecto, en otro caso ingrese un 0: ");
        scanf("%d", &efecto);
        if(!efecto){
            printf("+===================================================================+\n\n");
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
    printf("+===================================================================+\n\n");
    return seleccion;
}

/*
 * Function: SRR
 * ----------------------------
 *   Función de activación de efecto tipo ??
 *
 *   int player_id: id de jugador
 *
 *   Returns: int, 0 en caso de no activar el efecto, el efecto en rango [1...5] etoc.
 */
int SSR(int player_id){
    int seleccion;
    printf("\n+==========================CELDA=ESPECIAL===========================+\n");
    if(!player_id){
        int efecto;
        printf("Quiere activar el efecto '\?'.\nIngrese 1 para activar el efecto, en otro caso ingrese un 0: ");
        scanf("%d", &efecto);
        if(!efecto){
            printf("+===================================================================+\n\n");
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
    printf("+===================================================================+\n\n");
    return seleccion;
}

/*
 * Function: nextNormalPos
 * ----------------------------
 *   Funci[on que retorna la siguiente posición normal (en caso que exista)
 *   desde la posición de jugador player_id en dirección de tablero.
 *
 *   Board* b: Puntero al struct de tablero.
 *   int player_id: id de jugador
 *
 *   Returns: int, posición de siguiente casilla blanca (normal) si existe, etoc la posición actual de jugador.
 */
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

/*
 * Function: teleportPlayer
 * ----------------------------
 *   Teleporta el jugador player_id a nueva posición newpos.
 *
 *   Board* b: Puntero al struct de tablero.
 *   int player_id: id de jugador
 *	 int newpos: nueva posición en tablero.
 *
 *   Returns: void, sin retorno.
 */
void teleportPlayer(Board* b, int player_id, int newpos){
    b->pos[player_id] = newpos;
}

/*
 * Function: firstPlayer
 * ----------------------------
 *   Retorna la posición del jugador que va ganando (según la dirección de tablero)
 *
 *   Board* b: Puntero al struct de tablero.
 *
 *   Returns: int, la posición del jugador ganador.
 */
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

/*
 * Function: lastPlayer
 * ----------------------------
 *   Retorna la posición del jugador que va último (según la dirección de tablero)
 *
 *   Board* b: Puntero al struct de tablero.
 *
 *   Returns: int, la posición del jugador que va en última posición.
 */
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

/*
 * Function: movePlayer
 * ----------------------------
 *   Avanza al jugador en roll posiciones en el tablero
 *	 en el caso de ser posible.
 *
 *   Board* b: Puntero al struct de tablero.
 *   int player_id: id de jugador
 *   int roll: posiciones para avanzar
 *
 *   Returns: void, sin retorno.
 */
void movePlayer(Board* b, int player_id, int roll){
    b->pos[player_id] += roll*b->dir;
    if(b->pos[player_id] > 28) b->pos[player_id] = 28;
    if(b->pos[player_id] < 0) b->pos[player_id] = 0;
}


/*
 * Function: printRow
 * ----------------------------
 *   Imprime la fila del tablero.
 *
 *   Board* b: Puntero al struct de tablero.
 *   int begin: la primera casilla de que parte la fila.
 *   int end: la casilla en que termina la fila.
 *   int inc: la dirección 
 *   int align: el indicador alineamiento a la derecho o izquierda 
 *
 *   Returns: void, sin retorno.
 */
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

/*
 * Function: printBoard
 * ----------------------------
 *   Función que a través de las llamadas a printRow
 *	 imprime el tablero deseado.
 *
 *   Board* b: Puntero al struct de tablero.
 *
 *   Returns: void, sin retorno.
 */
void printBoard(Board* b){
   printRow(b, 20, 29, 1, 0);
   printRow(b, 19, 20, 1, 0);
   printRow(b, 18, 9, -1, 0);
   printRow(b, 9, 10, 1, 1);
   printRow(b, 0, 9, 1, 0);
}

/*
 * Function: checkWinner
 * ----------------------------
 *   Analiza qué jugador ganó.
 *
 *   Board* b: Puntero al struct de tablero.
 *
 *   Returns: int, número de jugador ganador.
 */
int checkWinner(Board*b){
    int goal = (b->dir>0)?28:0;

    if(b->pos[0] == goal) return 1;
    else if(b->pos[1] == goal) return 2;
    else if(b->pos[2] == goal) return 3;
    else if(b->pos[3] == goal) return 4;
    else return 0;
}

/*
 * Function: reverseBoard
 * ----------------------------
 *   Invierte la dirección del tablero.
 *
 *   Board* b: Puntero al struct de tablero.
 *
 *   Returns: void, sin retorno.
 */
void reverseBoard(Board* b){
    b->dir *= -1;
    for(int i = 0; i<29; i++) b->board[i] *= -1;
}


/*
 * Function: sharedMemory
 * ----------------------------
 *   Inicia la memoria compartida de tamaño de tablero de juego.
 *
 *   Sin parametros
 *
 *   Returns: Board*, memoria compartida.
 */
Board* sharedMemory(){
    int protection = PROT_READ|PROT_WRITE;
    int flags = MAP_SHARED|MAP_ANONYMOUS;
    return mmap(NULL, sizeof(Board), protection, flags, -1, 0);
}

