#include <pthread.h>
#include "../include/input.h"
#include "../include/game.h"

void* inputThread(void*arg){
    fallingBlocksGame*game = (fallingBlocksGame*)arg;
    while(1){
        int ch = getch();

        pthread_mutex_lock(&(game->input.mutex));
        game->input.lastKey = ch;
        pthread_mutex_unlock(&(game->input.mutex));
        
        if(ch=='q'){
            break;
        }
    }
    return NULL;
}

int getChoice(fallingBlocksGame*game){
        pthread_mutex_lock(&game->input.mutex);
        int choice = game->input.lastKey;
        game->input.lastKey = 0;
        pthread_mutex_unlock(&game->input.mutex);
        return choice;
}