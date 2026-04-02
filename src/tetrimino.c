#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/tetrimino.h"
#include "../include/constants.h"
#include "../include/utilities.h"

void deleteTetrimino(Tetrimino *tetrimino)
{
    if (tetrimino == NULL) return;
    
    // Free matrix
    if (tetrimino->matrix != NULL) {
        freeMatrix((tetrimino->matrix),tetrimino->matrixSize);
        tetrimino->matrix = NULL;
    }
    
    // Free location
    if (tetrimino->location != NULL) {
        free(tetrimino->location);
        tetrimino->location = NULL;
    }
    
    free(tetrimino);
}

static Tetrimino* createBaseTetrimino(int size, char letter)
{
    if (size <= 0 || size > 4) {
        fprintf(stderr, "ERROR: Invalid matrix size %d\n", size);
        return NULL;
    }
    
    Tetrimino *newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    if (newTetrimino == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate Tetrimino structure\n");
        return NULL;
    }
    
    newTetrimino->matrix = NULL;
    newTetrimino->location = NULL;
    newTetrimino->matrixSize = size;
    newTetrimino->tetriminoLetter = letter;
    
    newTetrimino->location = (Point*)malloc(sizeof(Point));
    if (newTetrimino->location == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate Point structure\n");
        free(newTetrimino);
        return NULL;
    }
    
    newTetrimino->location->x = COLUMNS / 2 - 2;
    newTetrimino->location->y = 0;
    
    newTetrimino->matrix = initializeMatrix(size);
    if (newTetrimino->matrix == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate matrix\n");
        free(newTetrimino->location);
        free(newTetrimino);
        return NULL;
    }
    
    return newTetrimino;
}

Tetrimino* createLTetrimino()
{
    Tetrimino *newTetrimino = createBaseTetrimino(3, 'L');
    if (newTetrimino == NULL) return NULL;
    
    // [[0,1,0],
    //  [0,1,0],
    //  [0,1,1]]
    newTetrimino->matrix[0][1] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[2][1] = 1;
    newTetrimino->matrix[2][2] = 1;
    
    return newTetrimino;
}

Tetrimino* createJTetrimino()
{
    Tetrimino *newTetrimino = createBaseTetrimino(3, 'J');
    if (newTetrimino == NULL) return NULL;
    
    // [[0,1,0],
    //  [0,1,0],
    //  [1,1,0]]
    newTetrimino->matrix[0][1] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[2][1] = 1;
    newTetrimino->matrix[2][0] = 1;
    
    return newTetrimino;
}

Tetrimino* createZTetrimino()
{
    Tetrimino *newTetrimino = createBaseTetrimino(3, 'Z');
    if (newTetrimino == NULL) return NULL;
    
    // [[0,0,1],
    //  [0,1,1],
    //  [0,1,0]]
    newTetrimino->matrix[0][2] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[1][2] = 1;
    newTetrimino->matrix[2][1] = 1;
    
    return newTetrimino;
}

Tetrimino* createSTetrimino()
{
    Tetrimino *newTetrimino = createBaseTetrimino(3, 'S');
    if (newTetrimino == NULL) return NULL;
    
    // [[1,0,0],
    //  [1,1,0],
    //  [0,1,0]]
    newTetrimino->matrix[0][0] = 1;
    newTetrimino->matrix[1][0] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[2][1] = 1;
    
    return newTetrimino;
}

Tetrimino* createOTetrimino()
{
    Tetrimino *newTetrimino = createBaseTetrimino(2, 'O');
    if (newTetrimino == NULL) return NULL;
    
    // [[1,1],
    //  [1,1]]
    newTetrimino->matrix[0][0] = 1;
    newTetrimino->matrix[0][1] = 1;
    newTetrimino->matrix[1][0] = 1;
    newTetrimino->matrix[1][1] = 1;
    
    return newTetrimino;
}

Tetrimino* createITetrimino()
{
    Tetrimino *newTetrimino = createBaseTetrimino(4, 'I');
    if (newTetrimino == NULL) return NULL;
    
    // [[0,1,0,0],
    //  [0,1,0,0],
    //  [0,1,0,0],
    //  [0,1,0,0]]
    newTetrimino->matrix[0][1] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[2][1] = 1;
    newTetrimino->matrix[3][1] = 1;
    
    return newTetrimino;
}

Tetrimino* createTTetrimino()
{
    Tetrimino *newTetrimino = createBaseTetrimino(3, 'T');
    if (newTetrimino == NULL) return NULL;
    
    // [[0,0,0],
    //  [1,1,1],
    //  [0,1,0]]
    newTetrimino->matrix[1][0] = 1;
    newTetrimino->matrix[1][1] = 1;
    newTetrimino->matrix[1][2] = 1;
    newTetrimino->matrix[2][1] = 1;
    
    return newTetrimino;
}

Tetrimino* generateRandomTetrimino()
{
    int num = rand() % NUMBER_OF_TETRIMINOS;
    Tetrimino *t = NULL;
    
    switch (num) {
        case 0:
            t = createLTetrimino();
            break;
        case 1:
            t = createTTetrimino();
            break;
        case 2:
            t = createOTetrimino();
            break;
        case 3:
            t = createITetrimino();
            break;
        case 4:
            t = createJTetrimino();
            break;
        case 5:
            t = createSTetrimino();
            break;
        case 6:
            t = createZTetrimino();
            break;
        default:
            return NULL;
    }
    
    if (t == NULL) {
        fprintf(stderr, "ERROR: Failed to generate tetrimino type");
        return NULL;
    }
    
    return t;
}

void turnTetriminoClockwise(Tetrimino *tetrimino)
{
    if (tetrimino == NULL) {
        return;
    }
    
    if (tetrimino->matrix == NULL) {
        return;
    }
    
    int size = tetrimino->matrixSize;
    
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int temp = tetrimino->matrix[i][j];
            tetrimino->matrix[i][j] = tetrimino->matrix[j][i];
            tetrimino->matrix[j][i] = temp;
        }
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size / 2; j++) {
            int temp = tetrimino->matrix[i][j];
            tetrimino->matrix[i][j] = tetrimino->matrix[i][size - 1 - j];
            tetrimino->matrix[i][size - 1 - j] = temp;
        }
    }
}

Tetrimino* copyTetrimino(Tetrimino *tetrimino)
{
    if (tetrimino == NULL) {
        return NULL;
    }
    
    if (tetrimino->matrix == NULL) {
        return NULL;
    }
    
    if (tetrimino->location == NULL) {
        return NULL;
    }
    
    Tetrimino *newTetrimino = (Tetrimino*)malloc(sizeof(Tetrimino));
    if (newTetrimino == NULL) {
        return NULL;
    }
    
    newTetrimino->location = (Point*)malloc(sizeof(Point));
    if (newTetrimino->location == NULL) {
        free(newTetrimino);
        return NULL;
    }
    
    newTetrimino->location->x = tetrimino->location->x;
    newTetrimino->location->y = tetrimino->location->y;
    newTetrimino->matrixSize = tetrimino->matrixSize;
    newTetrimino->tetriminoLetter = tetrimino->tetriminoLetter;
    
    newTetrimino->matrix = initializeMatrix(tetrimino->matrixSize);
    if (newTetrimino->matrix == NULL) {
        free(newTetrimino->location);
        free(newTetrimino);
        return NULL;
    }
    
    for (int i = 0; i < tetrimino->matrixSize; i++) {
        if (tetrimino->matrix[i] == NULL) {
            deleteTetrimino(newTetrimino);
            return NULL;
        }
        for (int j = 0; j < tetrimino->matrixSize; j++) {
            newTetrimino->matrix[i][j] = tetrimino->matrix[i][j];
        }
    }
    
    return newTetrimino;
}

int getTetriminoColor(Tetrimino *t)
{
    if (t == NULL) {
        return 0;
    }
    
    switch (t->tetriminoLetter) {
        case 'I':
            return 1;
        case 'O':
            return 2;
        case 'T':
            return 3;
        case 'S':
            return 4;
        case 'Z':
            return 5;
        case 'J':
            return 6;
        case 'L':
            return 7;
        default:
            return 0;
    }
}