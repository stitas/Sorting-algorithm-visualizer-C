#ifndef ALGORITHMS_H
#define ALGORITHMS_H

void bubbleSort(double *cols, int colCount);
void selectionSort(double *cols, int colCount);
void insertionSort(double *cols, int colCount);
void mergeSort(double *cols, int l, int r, int colCount);
void quickSort(double *cols, int low, int high, int colCount);
void heapSort(double *cols, int colCount);
void cycleSort(double *cols, int colCount);

#endif