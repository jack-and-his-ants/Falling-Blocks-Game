#pragma once

#include "game.h"

typedef enum {
    MENU_MAIN,
    GAME_PLAYING,
    GAME_QUIT
} GameState;

typedef struct {
    char name[20];
    int score;
} HighScore;

GameState showMainMenu();
void saveHighScore(const char *name, int score);
HighScore loadHighScore();
void getPlayerName(char *name, int maxLen);
