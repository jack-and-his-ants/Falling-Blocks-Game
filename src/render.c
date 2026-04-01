#include <ncurses.h>
#include "../include/constants.h"
#include "../include/game.h"
#include "../include/render.h"

WINDOW *initializePlayWindow()
{

    WINDOW *win = newwin(WINDOW_HEIGHT(ROWS), WINDOW_WIDTH(COLUMNS), 1, 0);
    return win;
}
WINDOW *initializeStatsWindow()
{
    WINDOW *win = newwin(STATUS_WINDOW_HEIGHT, STATUS_WINDOW_WIDTH, 1, 24);
    return win;
}
WINDOW *initializeCursesMainWindow()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    WINDOW *win = newwin(WINDOW_HEIGHT(ROWS) + 2, WINDOW_WIDTH(COLUMNS) + STATUS_WINDOW_WIDTH, 0, 0);

    return win;
}

void printField(WINDOW *win, int **field)
{
    for (int i = 0; i < ROWS; i++)
    {
        mvwprintw(win, i, 0, "<!");
        for (int j = 0; j < COLUMNS; j++)
        {
            if (field[i][j] == 0)
            {
                mvwprintw(win, i, j * 2 + 2, " .");
            }
            else
            {
                wattron(win, COLOR_PAIR(field[i][j]));
                mvwprintw(win, i, j * 2 + 2, "[]");
                wattroff(win, COLOR_PAIR(field[i][j]));
            }
        }
        mvwprintw(win, i, COLUMNS * 2 + 2, "!>");
    }
    mvwprintw(win, ROWS, 0, "<!");
    for (int j = 0; j < COLUMNS; j++)
    {
        mvwprintw(win, ROWS, j * 2 + 2, "**");
    }
    mvwprintw(win, ROWS, COLUMNS * 2 + 2, "!>");
}

void printStatus(fallingBlocksGame *game, double currentTime)
{
    WINDOW *win = game->statWin;

    // Borders
    for (int i = 0; i < STATUS_WINDOW_HEIGHT; i++)
    {
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
}

void printNextTetrimino(fallingBlocksGame *game)
{
    WINDOW *win = game->statWin;
    Tetrimino *t = game->nextTetrimino;
    if (!t)
        return;

    int startY = 10;
    int startX = 3; // było 4

    mvwprintw(win, startY - 1, startX, "~~~~~~~~~~~~~~~~");

    for (int i = 0; i < 6; i++)
    {
        mvwprintw(win, startY + i, startX, "|");
        mvwprintw(win, startY + i, startX + 15, "|");
    }

    mvwprintw(win, startY + 6, startX, "~~~~~~~~~~~~~~~~");

    // Tetrimino
    int offsetX = startX + 4;
    int offsetY = startY + 1;
    int color = getTetriminoColor(t);
    if (t->matrixSize == 2)
    {
        offsetX += 1;
        offsetY += 1;
    }
    for (int i = 0; i < t->matrixSize; i++)
    {
        for (int j = 0; j < t->matrixSize; j++)
        {
            if (t->matrix[i][j])
            {
                wattron(win, COLOR_PAIR(color));

                mvwprintw(win, offsetY + i, offsetX + j * 2, "[]");

                wattroff(win, COLOR_PAIR(color));
            }
        }
    }
}
void PrintMainWindow(fallingBlocksGame *game)
{
    for (int i = 0; i < WINDOW_WIDTH(COLUMNS) + STATUS_WINDOW_WIDTH; i += 2)
    {
        mvwprintw(game->mainWin, 0, i, "/\\");
    }

    for (int i = 0; i < WINDOW_WIDTH(COLUMNS) + STATUS_WINDOW_WIDTH; i += 2)
    {
        mvwprintw(game->mainWin, WINDOW_HEIGHT(ROWS) + 1, i, "/\\");
    }
}

void render(double currentTime, fallingBlocksGame*game){
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
}