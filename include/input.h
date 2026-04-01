#pragma once
#include <pthread.h>
typedef struct fallingBlocksGame fallingBlocksGame;

typedef struct inputState
{
    int lastKey;
    pthread_mutex_t mutex;
} inputState;

void *inputThread(void *arg);
int getChoice(fallingBlocksGame*game);