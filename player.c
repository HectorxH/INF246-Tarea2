#include "player.h"

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

void sendToPlayer(Player* p, int* msg){
    write(p->to_player[WRITE], msg, sizeof(int));
}

void readToPlayer(Player* p, int* msg){
    read(p->to_player[READ], msg, sizeof(int));
}

void sendFromPlayer(Player* p, int* msg){
    write(p->from_player[WRITE], msg, sizeof(int));
}

void readFromPlayer(Player* p, int* msg){
    read(p->from_player[READ], msg, sizeof(int));
}

Board* sharedMemory(){
    int protection = PROT_READ|PROT_WRITE;
    int flags = MAP_SHARED|MAP_ANONYMOUS;
    return mmap(NULL, sizeof(Board), protection, flags, -1, 0);
}