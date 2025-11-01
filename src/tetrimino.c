#include <stdlib.h>
#include "../include/tetrimino.h"
#include "../constants.h"
#include "../include/utilities.h"

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