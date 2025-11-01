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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/tetrimino.h"
#include "../constants.h"
#include "../include/utilities.h"
// [[0,1,0],
//  [0,1,0],
//  [0,1,1]]







typedef struct fallingBlocksGame
{
    WINDOW*mainWin;
    WINDOW*playWin;
    WINDOW*statWin;
    Tetrimino*currentTetrimino;
    Tetrimino*nextTetrimino;
    int**gameField;
    int points;
    unsigned int time;
}fallingBlocksGame;

/////////////////////////////////////////////////////////////////////////
////////////////////// INITIALIZERS /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


WINDOW*initializeCursesWindow(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    WINDOW*win=newwin(WINDOW_HEIGHT(ROWS),WINDOW_WIDTH(COLUMNS),1,1);
    return win;
}


fallingBlocksGame*initializeGame(){
    fallingBlocksGame *newGame = (fallingBlocksGame*)malloc(sizeof(fallingBlocksGame));

    newGame->gameField = initializeField();
    newGame->currentTetrimino = generateRandomTetrimino();
    newGame->nextTetrimino = generateRandomTetrimino();
    newGame->points = 0;
    newGame->time=0;
    newGame->playWin=initializeCursesWindow();

    return newGame;
}
void pushTetriminoOnScreen(fallingBlocksGame*game){
    Tetrimino*tetrimino=game->currentTetrimino;
    for(int i = 0 ; i < tetrimino->matrixSize;i++){
        for(int j = 0 ; j < game->currentTetrimino->matrixSize;j++){
            if(tetrimino->matrix[i][j]){
            game->gameField[tetrimino->location->y + i][tetrimino->location->x + j] = 1;
            }
        }
    }
}

void clearTetriminoView(fallingBlocksGame*game){
    Tetrimino*tetrimino=game->currentTetrimino;
    for(int i = 0 ; i < tetrimino->matrixSize;i++){
        for(int j = 0 ; j < tetrimino->matrixSize;j++){
            if(tetrimino->matrix[i][j]){
            game->gameField[tetrimino->location->y + i][tetrimino->location->x + j] = 0;
            }
        }
    }
}

void printField(WINDOW*win,int**field){
    for(int i = 0 ; i < ROWS ; i++ ){
        mvwprintw(win,i,0,"<!");
        for(int j = 0 ; j < COLUMNS ; j++){
            if (field[i][j]==0){
                mvwprintw(win,i,j*2+2," .");
            }else{
                mvwprintw(win,i,j*2+2,"[]");
            }
        }
        mvwprintw(win,i,COLUMNS*2+2,"!>");

    }
    mvwprintw(win,ROWS,0,"<!");
    for(int j = 0 ; j < COLUMNS ; j++){
                mvwprintw(win,ROWS,j*2+2,"**");
    }
    mvwprintw(win,ROWS,COLUMNS*2+2,"!>");
    for(int j = 0 ; j < COLUMNS ; j++){
                mvwprintw(win,ROWS+1,j*2+2,"\\/");
    }
}
void printStatus(WINDOW*statwin){

}

int correctMove(int direction, fallingBlocksGame*game){
    Tetrimino*tempTetrimino = copyTetrimino(game->currentTetrimino);
    clearTetriminoView(game);
    if (direction == TURN_CLOCKWISE){
        turnTetriminoClockwise(tempTetrimino,game->gameField);
    }else if (direction == MOVE_RIGHT){
        tempTetrimino->location->x += 1;
    }else if (direction == MOVE_DOWN){
        tempTetrimino->location->y += 1;
    }else if (direction == MOVE_LEFT){
        tempTetrimino->location->x -= 1;
    }
    
    for(int x = 0 ; x < tempTetrimino->matrixSize;x++){
        for(int y = 0 ; y < tempTetrimino->matrixSize;y++){   
            if(tempTetrimino->matrix[y][x]){

                if(tempTetrimino->location->x+x<0 || tempTetrimino->location->x+x>=COLUMNS || tempTetrimino->location->y+y<0 || tempTetrimino->location->y+y>=ROWS){
                    pushTetriminoOnScreen(game);
                    return 0;
                }
                if(game->gameField[tempTetrimino->location->y + y][tempTetrimino->location->x + x] == 1){
                    pushTetriminoOnScreen(game);
                    return 0;
                }


            }
        }
    }
    pushTetriminoOnScreen(game);
    return 1;
}


int checkFullRows(fallingBlocksGame*game){
    int**field=game->gameField;
    int pointsToAdd=0,fullRowCount=0;
    for(int i=0;i<ROWS;i++){

        int full=1;
        for(int j = 0 ; j < COLUMNS ; j++){
            if(field[i][j]==0){
                full=0;
                break;
        }}
        if (full) {
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < COLUMNS; j++) {
                    field[k][j] = field[k - 1][j];
                }
            }
            for (int j = 0; j < COLUMNS; j++) {
                field[0][j] = 0;
            }
            fullRowCount+=1;
        }
        pointsToAdd=10*fullRowCount;
    }
    game->points+=pointsToAdd;
    return 0;
}


void moveTetrimino(int direction, fallingBlocksGame*game){
    if(!correctMove(direction,game)){
        return;
    }
    clearTetriminoView(game);
    if (direction == TURN_CLOCKWISE){
        turnTetriminoClockwise(game->currentTetrimino,game->gameField);
    }else if (direction == MOVE_RIGHT){
        game->currentTetrimino->location->x += 1;
    }else if (direction == MOVE_DOWN){
        game->currentTetrimino->location->y += 1;
    }else if (direction == MOVE_LEFT){
        game->currentTetrimino->location->x -= 1;
    }

    
}
void changeTetrimino(fallingBlocksGame*game){
    deleteTetrimino(game->currentTetrimino);
    game->currentTetrimino=game->nextTetrimino;
    game->nextTetrimino=generateRandomTetrimino();
}

int main(){
    srand(time(NULL));
    fallingBlocksGame*game=initializeGame();
    nodelay(stdscr,1);
    noecho();
    unsigned int startTime=(clock()/CLOCKS_PER_MILISEC);
    unsigned int compareTime = clock();
    int choice;
    int elapsed_turns=0;

    while((choice=wgetch(stdscr))!='q'){
        unsigned int timeDiff = (clock() - compareTime+elapsed_turns*(DELAY_TIME))/(CLOCKS_PER_MILISEC);
        if(timeDiff>1000){
            if(!correctMove(MOVE_DOWN,game)){
                checkFullRows(game);
                changeTetrimino(game);
                if(!correctMove(MOVE_DOWN,game)){
                    break;
                }
            }else{
                moveTetrimino(MOVE_DOWN,game);
                
            }

            compareTime=clock();
            elapsed_turns=0;
        }
        moveTetrimino(choice,game);
        flushinp();
        pushTetriminoOnScreen(game);
        printField(game->playWin,game->gameField);
        wrefresh(game->playWin);
        
        usleep(DELAY_TIME);
        elapsed_turns+=1;
    }
}