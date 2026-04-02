#pragma once

#include "tetrimino.h"
#include <ncurses.h>
#include <pthread.h>
#include "input.h"



typedef struct fallingBlocksGame
{
    WINDOW *mainWin;
    WINDOW *playWin;
    WINDOW *statWin;
    inputState input;
    Tetrimino *currentTetrimino;
    Tetrimino *nextTetrimino;
    int **gameField;
    int points;
    double time;
    char blocked;
} fallingBlocksGame;

fallingBlocksGame *initializeGame();
void destroyGame(fallingBlocksGame *game);
void clearTetriminoView(fallingBlocksGame *game);
void pushTetriminoOnScreen(fallingBlocksGame *game);

int correctMove(int direction, fallingBlocksGame *game);
int checkFullRows(fallingBlocksGame *game);
void moveTetrimino(int direction, fallingBlocksGame *game);
void changeTetrimino(fallingBlocksGame *game);
void deleteGame(fallingBlocksGame**game);