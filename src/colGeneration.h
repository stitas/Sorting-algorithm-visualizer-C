#ifndef COLGENERATION_H
#define COLGENERATION_H
#include "raylib.h"

double *generateCols(int displayHeight, int colCount);
void drawCols(double *cols, int colCount, int indexOne, int indexTwo);

#endif