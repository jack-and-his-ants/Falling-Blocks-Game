#include "../include/utilities.h"
#include "../constants.h"
#include <stdlib.h>

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