#include <ncurses.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/constants.h"
#include "../include/utilities.h"
#include "../include/render.h"
#include "../include/input.h"

fallingBlocksGame *initializeGame()
{
    fallingBlocksGame *newGame = (fallingBlocksGame *)malloc(sizeof(fallingBlocksGame));
    newGame->blocked=0;
    newGame->input.lastKey=0;
    pthread_mutex_init(&(newGame->input.mutex),NULL);

    newGame->gameField = initializeField();
    newGame->currentTetrimino = generateRandomTetrimino();
    newGame->nextTetrimino = generateRandomTetrimino();

    newGame->points = 0;
    newGame->time = 0;
    newGame->mainWin = initializeCursesMainWindow();
    newGame->playWin = initializePlayWindow();
    newGame->statWin = initializeStatsWindow();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);    // I
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);  // O
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK); // T
    init_pair(4, COLOR_GREEN, COLOR_BLACK);   // S
    init_pair(5, COLOR_RED, COLOR_BLACK);     // Z
    init_pair(6, COLOR_BLUE, COLOR_BLACK);    // J
    init_pair(7, COLOR_WHITE, COLOR_BLACK);   // L

    return newGame;
}

void pushTetriminoOnScreen(fallingBlocksGame *game)
{
    Tetrimino *tetrimino = game->currentTetrimino;
    int color = getTetriminoColor(tetrimino);
    for (int i = 0; i < tetrimino->matrixSize; i++)
    {

        for (int j = 0; j < game->currentTetrimino->matrixSize; j++)
        {
            if (tetrimino->matrix[i][j])
            {
                game->gameField[tetrimino->location->y + i][tetrimino->location->x + j] = color;
            }
        }
    }
}

void clearTetriminoView(fallingBlocksGame *game)
{
    Tetrimino *tetrimino = game->currentTetrimino;
    for (int i = 0; i < tetrimino->matrixSize; i++)
    {
        for (int j = 0; j < tetrimino->matrixSize; j++)
        {
            if (tetrimino->matrix[i][j] != 0)
            {
                game->gameField[tetrimino->location->y + i][tetrimino->location->x + j] = 0;
            }
        }
    }
}

int correctMove(int direction, fallingBlocksGame *game)
{
    Tetrimino *tempTetrimino = copyTetrimino(game->currentTetrimino);
    clearTetriminoView(game);
    if (direction == TURN_CLOCKWISE)
    {
        turnTetriminoClockwise(tempTetrimino);
    }
    else if (direction == MOVE_RIGHT)
    {
        tempTetrimino->location->x += 1;
    }
    else if (direction == MOVE_DOWN)
    {
        tempTetrimino->location->y += 1;
    }
    else if (direction == MOVE_LEFT)
    {
        tempTetrimino->location->x -= 1;
    }

    for (int x = 0; x < tempTetrimino->matrixSize; x++)
    {
        for (int y = 0; y < tempTetrimino->matrixSize; y++)
        {
            if (tempTetrimino->matrix[y][x])
            {

                if (tempTetrimino->location->x + x < 0 || tempTetrimino->location->x + x >= COLUMNS || tempTetrimino->location->y + y < 0 || tempTetrimino->location->y + y >= ROWS)
                {
                    return 0;
                }
                if (game->gameField[tempTetrimino->location->y + y][tempTetrimino->location->x + x] != 0)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int checkFullRows(fallingBlocksGame *game)
{
    int **field = game->gameField;
    int pointsToAdd = 0, fullRowCount = 0;
    for (int i = 0; i < ROWS; i++)
    {

        int full = 1;
        for (int j = 0; j < COLUMNS; j++)
        {
            if (field[i][j] == 0)
            {
                full = 0;
                break;
            }
        }
        if (full)
        {
            for (int k = i; k > 0; k--)
            {
                for (int j = 0; j < COLUMNS; j++)
                {
                    field[k][j] = field[k - 1][j];
                }
            }
            for (int j = 0; j < COLUMNS; j++)
            {
                field[0][j] = 0;
            }
            fullRowCount += 1;
        }
        pointsToAdd = 10 * fullRowCount * fullRowCount;
    }
    game->points += pointsToAdd;
    return 0;
}

void moveTetrimino(int direction, fallingBlocksGame *game)
{
    if (!correctMove(direction, game))
    {
        return;
    }
    clearTetriminoView(game);
    if (direction == TURN_CLOCKWISE)
    {
        turnTetriminoClockwise(game->currentTetrimino);
    }
    else if (direction == MOVE_RIGHT)
    {
        game->currentTetrimino->location->x += 1;
    }
    else if (direction == MOVE_DOWN)
    {
        game->currentTetrimino->location->y += 1;
    }
    else if (direction == MOVE_LEFT)
    {
        game->currentTetrimino->location->x -= 1;
    }else if (direction == HARD_DROP){
        while(correctMove(MOVE_DOWN,game)){
            game->currentTetrimino->location->y += 1;
        }
        game->blocked = 1;
    }
}
void changeTetrimino(fallingBlocksGame *game)
{
    pushTetriminoOnScreen(game);
    deleteTetrimino(game->currentTetrimino);
    game->currentTetrimino = game->nextTetrimino;
    game->nextTetrimino = generateRandomTetrimino();
}

