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





int main()
{
    srand(time(NULL) ^ getpid() ^ getMillis());
    fallingBlocksGame *game = initializeGame();
    pthread_t input;
    pthread_create(&input,NULL,inputThread,game);
    noecho();

    unsigned long compareTime = getMillis(),compareTimeForGravity = getMillis();
    unsigned long startTime = getMillis();
    int choice;
    double currentTime;
    int running = 1;
    unsigned long gravityTime = 1000;
    while (running)
    {
        choice = getChoice(game);
        if(choice=='q'){
            running=0;
        }
        currentTime = (double)(getMillis() - startTime) / 1000;
        unsigned long timeDiff = getMillis() - compareTime;
        if (getMillis()-compareTimeForGravity>1000 && gravityTime>=400){
            gravityTime-=5;
            compareTimeForGravity = getMillis();
        }
        if (timeDiff > gravityTime || game->blocked==1)
        {
            if (!correctMove(MOVE_DOWN, game))
            {

                changeTetrimino(game);
                checkFullRows(game);
                if (!correctMove(MOVE_DOWN, game))
                {
                    break;
                }
                game->blocked = 0;
            }
            else
            {
                moveTetrimino(MOVE_DOWN, game);
            }

            compareTime = getMillis();
        }

        moveTetrimino(choice, game);
        
        render(currentTime,game);

        usleep(DELAY_TIME);
    }
    
    pthread_join(input, NULL);
    return 0;
}