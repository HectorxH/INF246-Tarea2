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

Board* sharedMemory(){
    int protection = PROT_READ|PROT_WRITE;
    int flags = MAP_SHARED|MAP_ANONYMOUS;
    return mmap(NULL, sizeof(Board), protection, flags, -1, 0);
}