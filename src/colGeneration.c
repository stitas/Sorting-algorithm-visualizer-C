#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "colGeneration.h"
#include "raylib.h"
#include "globals.h"

void shuffleCols(double *cols, int colCount){
    srand(time(NULL));

    for(int i = 0; i < colCount; i++){
        int j = i + rand() / (RAND_MAX / (colCount - i) + 1);
        
        // Change position on the screen
        double temp = cols[i];
        cols[i] = cols[j];
        cols[j] = temp;
    }
}

void drawCols(double *cols, int colCount, int indexOne, int indexTwo){
    double colWidth = (double) (WINDOW_WIDTH - colCount) / colCount; // substract col count to leave space in beetwen cols
    double x = 0;

    ClearBackground(BLACK);

    for(int i = 0; i < colCount; i++){
        Color color = WHITE;
        if(i == indexOne){
            color = RED;
        } else if (i == indexTwo){
            color = GREEN;
        }

        Rectangle col = {x, COLUMN_DISPLAY_HEIGHT - cols[i], colWidth, cols[i]};

        DrawRectangleRec(col, color);

        x += colWidth + 1;
    }
}

double *generateCols(int displayHeight, int colCount){
    double *cols = malloc(sizeof(double) * colCount);
    double firstColHeight = (double) displayHeight / colCount;

    for(int i = 0; i < colCount; i++){
        cols[i] = (i + 1) * firstColHeight;
    }

    shuffleCols(cols, colCount);

    return cols;
}