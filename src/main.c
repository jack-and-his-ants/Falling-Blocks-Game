/*{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}*/
/*{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{ FALLING BLOCKS }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}*/
/*{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}*/

// GAME PROJECT:
/*
                        /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
                        <! . . . . . . . . . .!><! Time:            !>
                        <! . . . . . . . . . .!><! 158.72 s.        !>
                        <! . . . . . . . . . .!><!                  !>
                        <! . . . .[][] . . . .!><! Points:          !>
                        <! . . . .[] . . . . .!><! 93               !>
                        <! . . . .[] . . . . .!><!                  !>
                        <! . . . . . . . . . .!><! Next Tetrimino:  !>
                        <! . . . . . . . . . .!><!~~~~~~~~~~~~~~~~~~!>
                        <! . . . . . . . . . .!><!§                §!>
                        <! . . . . . . . . . .!><!§       []       §!>
                        <! . . . . . . . . . .!><!§       []       §!>
                        <! . . . . . . . . . .!><!§       []       §!>
                        <! . . . . . . . . . .!><!§       []       §!>
                        <! . . . . . . . . . .!><!§                §!>
                        <! . . . . . . . . . .!><!~~~~~~~~~~~~~~~~~~!>
                        <! . . . . . . . . . .!><! Best Player:     !>
                        <! . . . . . . . . . .!><! Jacek            !>
                        <! . . . . . . . . . .!><! High Score:      !>
                        <! . . . . . . . . . .!><! 127878           !>
                        <! . . . . . . . . . .!><!                  !>
                        <!********************!><!******************!>
                        \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

*/
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
// [[0,1,0],
//  [0,1,0],
//  [0,1,1]]




/////////////////////////////////////////////////////////////////////////
////////////////////// INITIALIZERS /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////



int main()
{
    srand(time(NULL) ^ getpid() ^ getMillis());
    fallingBlocksGame *game = initializeGame();
    pthread_t input;
    pthread_create(&input,NULL,inputThread,game);
    noecho();

    unsigned long compareTime = getMillis();
    unsigned long startTime = getMillis();
    int choice;
    double currentTime;
    int running = 1;
    while (running)
    {
        pthread_mutex_lock(&game->input.mutex);
        choice = game->input.lastKey;
        game->input.lastKey = 0;
        pthread_mutex_unlock(&game->input.mutex);
        if(choice=='q'){
            running=0;
        }
        currentTime = (double)(getMillis() - startTime) / 1000;
        unsigned long timeDiff = getMillis() - compareTime;
        if (timeDiff > 1000)
        {
            if (!correctMove(MOVE_DOWN, game))
            {
                checkFullRows(game);
                changeTetrimino(game);
                if (!correctMove(MOVE_DOWN, game))
                {
                    break;
                }
            }
            else
            {
                moveTetrimino(MOVE_DOWN, game);
            }

            compareTime = getMillis();
        }

        moveTetrimino(choice, game);
        pushTetriminoOnScreen(game);

        werase(game->mainWin);
        werase(game->playWin);
        werase(game->statWin);

        PrintMainWindow(game);
        printField(game->playWin, game->gameField);
        printStatus(game, currentTime);
        printNextTetrimino(game);

        wrefresh(game->mainWin);
        wrefresh(game->playWin);
        wrefresh(game->statWin);
        clearTetriminoView(game);
        usleep(DELAY_TIME);
    }
    
    pthread_join(input, NULL);
    return 0;
}