#include "raylib.h"
#include "colGeneration.h"
#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define INPUT_HEIGHT 50
#define INPUT_WIDTH 100
#define MIN_COLS 10
#define MAX_COLS 200

void DrawNumber(int number, int xPosition) {
    char text[20];
    sprintf(text, "Number: %d", number);  // Convert number to string
    DrawText(text, xPosition, 200, 20, DARKBLUE);
}

int main(){
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sorting Algorithm Visualizer");
    SetTargetFPS(60);

    int INPUT_CONTAINER_MIDDLE = WINDOW_HEIGHT - ((WINDOW_HEIGHT - COLUMN_DISPLAY_HEIGHT + INPUT_HEIGHT) / 2);

    Rectangle algoSelect = {20, INPUT_CONTAINER_MIDDLE, INPUT_WIDTH, INPUT_HEIGHT};
    char *algorithms = "Bubble Sort;Selection Sort;Insertion Sort;Merge Sort;Quick Sort;Heap Sort;Cycle Sort";
    int selectedAlgorithm = 0;
    int algoSelectClick = 0;
    GuiSetStyle(DROPDOWNBOX, DROPDOWN_ROLL_UP, 1);

    Rectangle colCountInput = {150, INPUT_CONTAINER_MIDDLE, INPUT_WIDTH, INPUT_HEIGHT};
    int colCount = 50;
    int colCountTemp = 50;
    int colCountInputClick = 0;

    Rectangle drawBtn = {280, INPUT_CONTAINER_MIDDLE, INPUT_WIDTH, INPUT_HEIGHT};

    double *cols = generateCols(COLUMN_DISPLAY_HEIGHT, colCount);

    while(!WindowShouldClose()){

        if(IsKeyPressed(KEY_S)){
            switch(selectedAlgorithm){
                case 0:
                    bubbleSort(cols, colCount);
                    break;
                case 1:
                    selectionSort(cols, colCount);
                    break;
                case 2:
                    insertionSort(cols, colCount);
                    break;
                case 3:
                    mergeSort(cols, 0, colCount - 1, colCount);
                    break;
                case 4:
                    quickSort(cols, 0, colCount - 1, colCount);
                    break;
                case 5:
                    heapSort(cols, colCount);
                    break;
                case 6:
                    cycleSort(cols, colCount);
                    break;
                default:
                    bubbleSort(cols, colCount);
                    break;
            }
        } 

        BeginDrawing();

        DrawText("SELECT ALGORITHM:", 20, INPUT_CONTAINER_MIDDLE - 20, 11, SKYBLUE);
        DrawText("COLUMN NUMBER:", 150, INPUT_CONTAINER_MIDDLE - 20, 11, SKYBLUE);
        DrawText("PRESS S TO START", 500, 737, 30, SKYBLUE);

        drawCols(cols, colCount, -1, -1);

        if(GuiDropdownBox(algoSelect, algorithms, &selectedAlgorithm, algoSelectClick)){
            if(algoSelectClick){
                algoSelectClick = 0;
            }
            else {
                algoSelectClick = 1;
            }
        }

        if(GuiValueBox(colCountInput, "", &colCountTemp, MIN_COLS, MAX_COLS, colCountInputClick)){
            if(colCountInputClick){
                colCountInputClick = 0;
            }
            else {
                colCountInputClick = 1;
            }
        }

        if(GuiButton(drawBtn, "DRAW")) {
            colCount = colCountTemp;
            cols = generateCols(COLUMN_DISPLAY_HEIGHT, colCount);
        }

        EndDrawing();

    }

    free(cols);
    CloseWindow();

    return 0;
}