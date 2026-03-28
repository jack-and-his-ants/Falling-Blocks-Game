/*{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}*/
/*{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{ FALLING BLOCKS }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}*/
/*{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}*/

#define STATUS_WINDOW_WIDTH 22
#define STATUS_WINDOW_HEIGHT 21
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
    double time;
}fallingBlocksGame;

/////////////////////////////////////////////////////////////////////////
////////////////////// INITIALIZERS /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


WINDOW*initializePlayWindow(WINDOW*parent){
    
    WINDOW*win=subwin(parent,WINDOW_HEIGHT(ROWS),WINDOW_WIDTH(COLUMNS),1,0);
    return win;
}
WINDOW*initializeStatsWindow(WINDOW*parent){
    WINDOW*win=subwin(parent,STATUS_WINDOW_HEIGHT,STATUS_WINDOW_WIDTH,1,24);
    return win;
}
WINDOW*initializeCursesMainWindow(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    WINDOW*win=newwin(WINDOW_HEIGHT(ROWS)+2,WINDOW_WIDTH(COLUMNS)+STATUS_WINDOW_WIDTH,0,0);
    return win;
}


fallingBlocksGame*initializeGame(){
    fallingBlocksGame *newGame = (fallingBlocksGame*)malloc(sizeof(fallingBlocksGame));

    newGame->gameField = initializeField();
    newGame->currentTetrimino = generateRandomTetrimino();
    newGame->nextTetrimino = generateRandomTetrimino();
    newGame->points = 0;
    newGame->time=0;
    newGame->mainWin=initializeCursesMainWindow();
    newGame->playWin=initializePlayWindow(newGame->mainWin);
    newGame->statWin=initializeStatsWindow(newGame->mainWin);

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
}

void printStatus(fallingBlocksGame*game,double currentTime){
    WINDOW*win = game->statWin;
    werase(win);
    
    
    // Borders
    for(int i = 0; i < STATUS_WINDOW_HEIGHT; i++ ){
        mvwprintw(win, i, 0, "<!");
        mvwprintw(win, i, STATUS_WINDOW_WIDTH - 2, "!>");
    }
    
    // Time
    mvwprintw(win, 2, 3, "Time:");
    mvwprintw(win, 3, 3, "%.2f s.", currentTime);
    
    // Points
    mvwprintw(win, 5, 3, "Points:");
    mvwprintw(win, 6, 3, "%d", game->points);
    
    // Next Tetrimino
    mvwprintw(win, 8, 3, "Next Tetrimino:");
    
    // Best Player
    mvwprintw(win, 17, 3, "Best Player:");
    mvwprintw(win, 18, 3, "Jacek");
    
    // High Score
    mvwprintw(win, 19, 3, "High Score:");
    mvwprintw(win, 20, 3, "%d", game->points);

    
    wrefresh(win);
}



void printNextTetrimino(fallingBlocksGame*game) {
    WINDOW* win = game->statWin;
    Tetrimino* t = game->nextTetrimino;
    
    if(!t) return;
    
    int startY = 10;
    int startX = 4;
    
    // Rysowanie ramki
    mvwprintw(win, startY - 1, startX - 2, "~~~~~~~~~~~~~~~~~~");
    
    for(int i = 0; i < 6; i++) {
        mvwprintw(win, startY + i, startX - 2, "§");
        mvwprintw(win, startY + i, startX + 16, "§");
    }
    
    mvwprintw(win, startY + 6, startX - 2, "~~~~~~~~~~~~~~~~~~");
    
    // Wyświetlanie tetrimino z odpowiednim przesunięciem
    switch(t->matrixSize) {
        case 2:  // O tetrimino (2x2)
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    if(t->matrix[i][j]) {
                        mvwprintw(win, startY + 2 + i, startX + 4 + j * 2, "[]");
                    }
                }
            }
            break;
            
        case 3:  // L, J, S, Z, T tetrimino (3x3)
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(t->matrix[i][j]) {
                        mvwprintw(win, startY + 2 + i, startX + 3 + j * 2, "[]");
                    }
                }
            }
            break;
            
        case 4:  // I tetrimino (4x4)
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    if(t->matrix[i][j]) {
                        mvwprintw(win, startY + 1 + i, startX + 2 + j * 2, "[]");
                    }
                }
            }
            break;
    }
    
    wrefresh(win);
}
void PrintMainWindow(fallingBlocksGame*game){
    for(int i=0;i<WINDOW_WIDTH(COLUMNS)+STATUS_WINDOW_WIDTH;i+=2){
        mvwprintw(game->mainWin,0,i,"/\\");
    }

    
    for(int i=0;i<WINDOW_WIDTH(COLUMNS)+STATUS_WINDOW_WIDTH;i+=2){
        mvwprintw(game->mainWin,WINDOW_HEIGHT(ROWS)+1,i,"/\\");
    }
}
unsigned long getMillis(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (unsigned long)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
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
        pointsToAdd=10*fullRowCount*fullRowCount;
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
    unsigned long compareTime = getMillis();
    unsigned long startTime = getMillis();
    int choice;
    double currentTime;
    while((choice=wgetch(stdscr))!='q'){
        currentTime = (double)(getMillis()-startTime)/1000;
        unsigned long timeDiff = getMillis() - compareTime;
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

            compareTime=getMillis();
        }
        
        moveTetrimino(choice,game);
        flushinp();
        pushTetriminoOnScreen(game);

        

        PrintMainWindow(game);

        printField(game->playWin,game->gameField);
        printStatus(game,currentTime);
        printNextTetrimino(game);

        wrefresh(game->mainWin);
        wrefresh(game->playWin);
        wrefresh(game->statWin);
        clearTetriminoView(game);
        usleep(DELAY_TIME);
    }
}