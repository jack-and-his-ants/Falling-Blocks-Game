#include "../include/utilities.h"
#include "../include/constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int** initializeMatrix(int size)
{
    int** matrix = (int**)malloc(sizeof(int*) * size);
    if (matrix == NULL) {
        fprintf(stderr, "ERROR: initializeMatrix - Failed to allocate row pointers");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        matrix[i] = NULL;
    }
    
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * size);
        if (matrix[i] == NULL) {
            fprintf(stderr, "ERROR: initializeMatrix - Failed to allocate row");
            
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
                matrix[j] = NULL;
            }
            free(matrix);
            return NULL;
        }
        
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }
    
    return matrix;
}

int** initializeField()
{
    int** field = (int**)malloc(sizeof(int*) * ROWS);
    if (field == NULL) {
        fprintf(stderr, "ERROR: initializeField - Failed to allocate row pointers\n");
        return NULL;
    }
    
    for (int i = 0; i < ROWS; i++) {
        field[i] = NULL;
    }
    
    for (int i = 0; i < ROWS; i++) {
        field[i] = (int*)malloc(sizeof(int) * COLUMNS);
        if (field[i] == NULL) {
            fprintf(stderr, "ERROR: initializeField - Failed to allocate row");
            
            for (int j = 0; j < i; j++) {
                free(field[j]);
                field[j] = NULL;
            }
            free(field);
            return NULL;
        }
        for (int j = 0; j < COLUMNS; j++) {
            field[i][j] = 0;
        }
    }
    
    return field;
}

void freeMatrix(int** matrix, int size)
{
    if (matrix == NULL) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        if (matrix[i] != NULL) {
            free(matrix[i]);
            matrix[i] = NULL;
        }
    }
    free(matrix);
}

void freeField(int** field)
{
    if (field == NULL) {
        return;
    }
    
    for (int i = 0; i < ROWS; i++) {
        if (field[i] != NULL) {
            free(field[i]);
            field[i] = NULL;
        }
    }
    free(field);
}

unsigned long getMillis(void)
{
    struct timespec ts;
    
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        fprintf(stderr, "ERROR: getMillis failed\n");
    }
    
    unsigned long milliseconds = (unsigned long)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    
    return milliseconds;
}