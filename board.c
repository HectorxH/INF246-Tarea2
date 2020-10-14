#include "board.h"

void newBoard(Board* b){
    b->dir = 1;
    for(int i = 0; i < 29; i++) b->board[i] = 0;

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

    for(int i=0; i<4; i++) b->players[i] = 0;
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

        if( b->players[0] == i) printf("1");
        else printf(" ");

        if( b->players[1] == i) printf("2");
        else printf(" ");

        if( b->players[2] == i) printf("3");
        else printf(" ");

        if( b->players[3] == i) printf("4");
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
    if(b->players[0] == 28) return 1;
    else if(b->players[1] == 28) return 2;
    else if(b->players[3] == 28) return 3;
    else if(b->players[1] == 28) return 4;
    else return 0;
}


