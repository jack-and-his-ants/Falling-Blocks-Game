#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "../include/menu.h"
#include "../include/constants.h"

#define HIGHSCORE_FILE "highscore.dat"

void saveHighScore(const char *name, int score) {
    HighScore current = loadHighScore();
    
    if (score > current.score) {
        HighScore newHighScore;
        strcpy(newHighScore.name, name);
        newHighScore.score = score;
        
        FILE *file = fopen(HIGHSCORE_FILE, "wb");
        if (file) {
            fwrite(&newHighScore, sizeof(HighScore), 1, file);
            fclose(file);
        }
    }
}

HighScore loadHighScore() {
    HighScore highScore = {"NONE", 0};
    FILE *file = fopen(HIGHSCORE_FILE, "rb");
    
    if (file) {
        fread(&highScore, sizeof(HighScore), 1, file);
        fclose(file);
    }
    
    return highScore;
}

void getPlayerName(char *name, int maxLen) {
    int ch;
    int pos = 0;
    
    clear();
    
    int startY = LINES / 2 - 2;
    int startX = (COLS - 40) / 2;
    
    attron(A_BOLD);
    mvprintw(startY, startX, "==============================");
    mvprintw(startY + 1, startX, "       ENTER YOUR NAME       ");
    mvprintw(startY + 2, startX, "==============================");
    attroff(A_BOLD);
    
    mvprintw(startY + 4, startX + 5, "Name (max 15 chars):");
    mvprintw(startY + 5, startX + 5, "> ");
    
    memset(name, 0, maxLen);
    pos = 0;
    
    int cursorX = startX + 7;
    int cursorY = startY + 5;
    
    curs_set(1);  
    echo(); 
    
    while (1) {
        move(cursorY, cursorX + pos);
        refresh();
        
        ch = getch();
        
        if (ch == '\n' || ch == '\r') {
            if (pos > 0) {
                break;
            }
        } else if (ch == 127 || ch == KEY_BACKSPACE || ch == 8) { 
            if (pos > 0) {
                pos--;
                name[pos] = '\0';
                mvprintw(cursorY, cursorX + pos, " ");
                move(cursorY, cursorX + pos);
            }
        } else if (pos < maxLen - 1 && ch >= 32 && ch <= 126) { 
            name[pos] = ch;
            pos++;
            name[pos] = '\0';
        }
    }
    
    noecho();
    curs_set(0);

    if (pos == 0) {
        strcpy(name, "PLAYER");
    }
}

GameState showMainMenu() {
    int ch;
    
    while (1) {
        clear();
        
        int startY = LINES / 2 - 4;
        int startX = (COLS - 30) / 2;
        
        attron(A_BOLD);
        mvprintw(startY, startX, "==============================");
        mvprintw(startY + 1, startX, "       FALLING BLOCKS        ");
        mvprintw(startY + 2, startX, "==============================");
        attroff(A_BOLD);
        
        mvprintw(startY + 4, startX + 5, "1. START GAME");
        mvprintw(startY + 5, startX + 5, "2. QUIT");
        
        HighScore highScore = loadHighScore();
        mvprintw(startY + 7, startX + 5, "High Score: %d by %s", 
                 highScore.score, highScore.name);
        
        mvprintw(startY + 9, startX + 5, "Press 1 or 2");
        
        refresh();
        
        ch = getch();
        
        if (ch == '1') {
            return GAME_PLAYING;
        } else if (ch == '2' || ch == 'q') {
            return GAME_QUIT;
        }
    }
}

void gameOver(char*playerName,fallingBlocksGame*game){
    clear();
    int startY = LINES / 2 - 3;
    int startX = (COLS - 30) / 2;
    
    attron(A_BOLD);
    mvprintw(startY, startX, "==============================");
    mvprintw(startY + 1, startX, "         GAME OVER!          ");
    mvprintw(startY + 2, startX, "==============================");
    attroff(A_BOLD);
    
    mvprintw(startY + 4, startX + 5, "Player: %s", playerName);
    mvprintw(startY + 5, startX + 5, "Your score: %d", game->points);
    
    HighScore highScore = loadHighScore();
    mvprintw(startY + 7, startX + 5, "High Score: %d by %s", 
             highScore.score, highScore.name);
    
    mvprintw(startY + 9, startX + 5, "Press q to exit");
    
    refresh();
    getch();
}