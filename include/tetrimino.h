#pragma once

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

void deleteTetrimino(Tetrimino*tetrimino);
Tetrimino*createLTetrimino();
Tetrimino*createJTetrimino();
Tetrimino*createZTetrimino();
Tetrimino*createSTetrimino();
Tetrimino*createOTetrimino();
Tetrimino*createITetrimino();
Tetrimino*createTTetrimino();
Tetrimino*generateRandomTetrimino();
void turnTetriminoClockwise(Tetrimino*tetrimino);
Tetrimino*copyTetrimino(Tetrimino*tetrimino);
int getTetriminoColor(Tetrimino *t);