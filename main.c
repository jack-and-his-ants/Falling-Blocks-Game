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

// [[0,1,0],
//  [0,1,0],
//  [0,1,1]]
#define ROWS 20
#define COLUMNS 10
#define WINDOW_WIDTH(width) (width*2+4)
#define WINDOW_HEIGHT(height) (height+2)
#define STAT_WINDOW_WIDTH 22
#define CLOCKS_PER_MILISEC (CLOCKS_PER_SEC/1000)
#define NOKEY ' '
#define NUMBER_OF_TETRIMINOS 7

#define TURN_CLOCKWISE KEY_UP
#define MOVE_RIGHT KEY_RIGHT
#define MOVE_DOWN KEY_DOWN
#define MOVE_LEFT KEY_LEFT
#define DELAY_TIME (CLOCKS_PER_MILISEC*10)




typedef struct Point
{
    int x;
    int y;
} Point;


typedef struct Tetrimino
{
    Point*location;
    int matrixSize;
    char tetriminoLetter;
    int**matrix;
} Tetrimino;

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
int**initializeField(){
    int**field=(int**)malloc(sizeof(int*)*ROWS);
    for (int i = 0;i<ROWS;i++){
        field[i]=(int*)malloc(sizeof(int)*COLUMNS);
        for(int j = 0 ; j < COLUMNS; j++){
            field[i][j]=0;
        }
    }
    return field;
}

WINDOW*initializeCursesWindow(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    WINDOW*win=newwin(WINDOW_HEIGHT(ROWS),WINDOW_WIDTH(COLUMNS),1,1);
    return win;
}
int**initializeMatrix(int size){
    int**matrix=(int**)malloc(sizeof(int*)*size);
    for( int i = 0 ; i < size ; i ++){
        matrix[i] = (int*)malloc(sizeof(int)*size);
    }
    for( int i = 0 ; i < size ; i ++){
        for( int j = 0 ; j < size ; j ++){
            matrix[j][i]=0;
        }
    }
    return matrix;
}
void deleteTetrimino(Tetrimino*tetrimino){
    for (int i = 0 ; i < (tetrimino)->matrixSize;i++){
        free((tetrimino)->matrix[i]);
    }
    free((tetrimino)->matrix);
    free((tetrimino)->location);
    return;
}
/*
    TETRIMINOS INITIALIZERS
*/
Tetrimino*createLTetrimino(){
    Tetrimino*newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    newTetrimino->location=(Point*)malloc(sizeof(Point));
    newTetrimino->location->x=COLUMNS/2-2;
    newTetrimino->location->y=0;
    newTetrimino->matrixSize=3;
    newTetrimino->matrix=initializeMatrix(3);
    newTetrimino->tetriminoLetter='L';
    // [[0,1,0],
    //  [0,1,0],
    //  [0,1,1]]
    newTetrimino->matrix[0][1] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[2][1] = 1;
    newTetrimino->matrix[2][2] = 1;
    return newTetrimino;
}

Tetrimino*createJTetrimino(){
    Tetrimino*newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    newTetrimino->location=(Point*)malloc(sizeof(Point));
    newTetrimino->location->x=COLUMNS/2-2;
    newTetrimino->location->y=0;
    newTetrimino->matrixSize=3;
    newTetrimino->matrix=initializeMatrix(3);
    newTetrimino->tetriminoLetter='J';
    // [[0,1,0],
    //  [0,1,0],
    //  [1,1,0]]
    newTetrimino->matrix[0][1] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[2][1] = 1;
    newTetrimino->matrix[2][0] = 1;
    return newTetrimino;
}
Tetrimino*createZTetrimino(){
    Tetrimino*newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    newTetrimino->location=(Point*)malloc(sizeof(Point));
    newTetrimino->location->x=COLUMNS/2-2;
    newTetrimino->location->y=0;
    newTetrimino->matrixSize=3;
    newTetrimino->matrix=initializeMatrix(3);
    newTetrimino->tetriminoLetter='Z';
    // [[0,0,1],
    //  [0,1,1],
    //  [0,1,0]]
    newTetrimino->matrix[0][2] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[1][2] = 1;
    newTetrimino->matrix[2][1] = 1;
    return newTetrimino;
}

Tetrimino*createSTetrimino(){
    Tetrimino*newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    newTetrimino->location=(Point*)malloc(sizeof(Point));
    newTetrimino->location->x=COLUMNS/2-2;
    newTetrimino->location->y=0;
    newTetrimino->matrixSize=3;
    newTetrimino->matrix=initializeMatrix(3);
    newTetrimino->tetriminoLetter='J';
    // [[1,0,0],
    //  [1,1,0],
    //  [0,1,0]]
    newTetrimino->matrix[0][0] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[1][0] = 1;
    newTetrimino->matrix[2][1] = 1;
    return newTetrimino;
}

Tetrimino*createOTetrimino(){
    Tetrimino*newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    newTetrimino->location=(Point*)malloc(sizeof(Point));
    newTetrimino->location->x=COLUMNS/2-2;
    newTetrimino->location->y=0;
    newTetrimino->matrixSize=2;
    newTetrimino->matrix=initializeMatrix(2);
    newTetrimino->tetriminoLetter='O';
    // [[1,1],
    //  [1,1]]
    newTetrimino->matrix[0][1] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[1][0] = 1;
    newTetrimino->matrix[0][0] = 1;
    return newTetrimino;
}

Tetrimino*createITetrimino(){
    Tetrimino*newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    newTetrimino->location=(Point*)malloc(sizeof(Point));
    newTetrimino->location->x=COLUMNS/2-2;
    newTetrimino->location->y=0;
    newTetrimino->matrixSize=4;
    newTetrimino->matrix=initializeMatrix(4);
    newTetrimino->tetriminoLetter='I';
    // [[0,0,0],
    //  [1,1,1],
    //  [0,1,0]]
    newTetrimino->matrix[0][1] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[2][1] = 1;
    newTetrimino->matrix[3][1] = 1;
    return newTetrimino;
}

Tetrimino*createTTetrimino(){
    Tetrimino*newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    newTetrimino->location=(Point*)malloc(sizeof(Point));
    newTetrimino->location->x=COLUMNS/2-2;
    newTetrimino->location->y=0;
    newTetrimino->matrixSize=3;
    newTetrimino->matrix=initializeMatrix(3);
    newTetrimino->tetriminoLetter='L';
    // [[0,0,0],
    //  [1,1,1],
    //  [0,1,0]]
    newTetrimino->matrix[0][1] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[2][1] = 1;
    newTetrimino->matrix[1][2] = 1;
    return newTetrimino;
}


Tetrimino*generateRandomTetrimino(){
    int num = rand()%NUMBER_OF_TETRIMINOS;
    if(num==0){
        return createLTetrimino();
    }
    if(num==1){
        return createTTetrimino();
    }
    if(num==2){
        return createOTetrimino();
    }
    if(num==3){
        return createITetrimino();
    }
    if(num==4){
        return createJTetrimino();
    }if(num==5){
        return createSTetrimino();
    }if(num==6){
        return createZTetrimino();
    }
    return NULL;
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
void turnTetriminoClockwise(Tetrimino*tetrimino,int**field){
    for (int i = 0; i < tetrimino->matrixSize; i++) {
        for (int j = i + 1; j < tetrimino->matrixSize; j++) {
            int temp = tetrimino->matrix[i][j];
            tetrimino->matrix[i][j]=tetrimino->matrix[j][i];
            tetrimino->matrix[j][i]=temp;
        }
    }
    for(int i=0;i<tetrimino->matrixSize;i++){
        for(int j = 0 ; j < tetrimino->matrixSize/2;j++){
            int temp = tetrimino->matrix[i][j];
            tetrimino->matrix[i][j]=tetrimino->matrix[i][tetrimino->matrixSize-1-j];
            tetrimino->matrix[i][tetrimino->matrixSize-1-j]=temp;
        }
    }
    
    
    return;
}
Tetrimino*copyTetrimino(Tetrimino*tetrimino){
    Tetrimino*newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    newTetrimino->location=(Point*)malloc(sizeof(Point));
    newTetrimino->location->x=tetrimino->location->x;
    newTetrimino->location->y=tetrimino->location->y;
    newTetrimino->matrixSize=tetrimino->matrixSize;
    newTetrimino->matrix=initializeMatrix(tetrimino->matrixSize);
    for(int i = 0 ; i < tetrimino->matrixSize;i++){
        for(int j = 0 ; j < tetrimino->matrixSize;j++){
            
            newTetrimino->matrix[i][j] = tetrimino->matrix[i][j];
            
        }
    }
    return newTetrimino;

    
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