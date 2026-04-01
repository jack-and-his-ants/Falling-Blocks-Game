#pragma once
#include "game.h"
#include "constants.h"

WINDOW *initializePlayWindow();
WINDOW *initializeStatsWindow();
WINDOW *initializeCursesMainWindow();

void printField(WINDOW *win, int **field);
void printStatus(fallingBlocksGame *game, double currentTime);
void printNextTetrimino(fallingBlocksGame *game);
void PrintMainWindow(fallingBlocksGame *game);

void render(double currentTime, fallingBlocksGame*game);