#include <curses.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/tetrimino.h"
#include "../include/constants.h"
#include "../include/utilities.h"
#include "../include/game.h"
#include "../include/render.h"
#include "../include/input.h"
#include "../include/menu.h"
#include "../include/gameplay.h"




int gameplay(){
    srand(time(NULL) ^ getpid() ^ getMillis());
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    
    GameState state = showMainMenu();
    
    if (state == GAME_QUIT) {
        endwin();
        return 0;
    }
    
    char playerName[20];
    getPlayerName(playerName, 20);

    // Start game
    clear();

    fallingBlocksGame *game = initializeGame();
    if(game==NULL) return 0;
    pthread_t input;
    pthread_create(&input, NULL, inputThread, game);
    
    unsigned long compareTime = getMillis(), compareTimeForGravity = getMillis();
    unsigned long startTime = getMillis();
    int choice;
    double currentTime;
    int running = 1;
    unsigned long gravityTime = 1000;
    
    while (running)
    {
        choice = getChoice(game);
        
        if (choice == 'q') {
            running = 0;
        }
        
        currentTime = (double)(getMillis() - startTime) / 1000;
        unsigned long timeDiff = getMillis() - compareTime;
        
        if (getMillis() - compareTimeForGravity > 1000 && gravityTime >= 400) {
            gravityTime -= 5;
            compareTimeForGravity = getMillis();
        }
        
        if (timeDiff > gravityTime || game->blocked == 1) {
            if (!correctMove(MOVE_DOWN, game)) {
                changeTetrimino(game);
                checkFullRows(game);
                saveHighScore(playerName,game->points);
                if (!correctMove(MOVE_DOWN, game)) {
                    running=0;
                    break;
                }
                game->blocked = 0;
            } else {
                moveTetrimino(MOVE_DOWN, game);
            }
            compareTime = getMillis();
        }
        
        moveTetrimino(choice, game);
        render(currentTime, game);
        usleep(DELAY_TIME);
    }
    saveHighScore(playerName,game->points);
    // Game over
    gameOver(playerName,game);

    destroyGame(game);
    pthread_join(input, NULL);
    endwin();
    
    return 0;
}