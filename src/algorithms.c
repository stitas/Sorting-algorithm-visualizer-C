#include "raylib.h"
#include "colGeneration.h"
#include <stdbool.h>
#include <stdio.h>

void swapCols(double *col1, double *col2){
    // Swap col position on screen
    double temp = *col1;
    *col1 = *col2;
    *col2 = temp;
}

void bubbleSort(double *cols, int colCount){
    int i, j;
    bool swapped;
    for (i = 0; i < colCount - 1; i++) {
        swapped = false;
        for (j = 0; j < colCount - i - 1; j++) {
            if (cols[j] > cols[j + 1]) {
                swapCols(&cols[j], &cols[j + 1]);
                swapped = true;
                BeginDrawing();
                drawCols(cols, colCount, j, j + 1);
                EndDrawing();
            }
        }

        if (!swapped){
            break;
        }
    }
}

void selectionSort(double *cols, int colCount) {
    for (int i = 0; i < colCount - 1; i++) {
      
        // Assume the current position holds
        // the minimum element
        int min_idx = i;
        
        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < colCount; j++) {
            if (cols[j] < cols[min_idx]) {
              
                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }
        
        // Move minimum element to its
        // correct position
        swapCols(&cols[i], &cols[min_idx]);

        BeginDrawing();
        drawCols(cols, colCount, i, min_idx);
        EndDrawing();
    }
}

void insertionSort(double *cols, int colCount)
{
    for (int i = 1; i < colCount; ++i) {
        int key = cols[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && cols[j] > key) {
            cols[j + 1] = cols[j];
            j = j - 1;
            BeginDrawing();
            drawCols(cols, colCount, j, j + 1);
            EndDrawing();
        }
        cols[j + 1] = key;
        drawCols(cols, colCount, j, i);

    }
}

void merge(double *cols, int l, int m, int r, int colCount){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = cols[l + i];
    for (j = 0; j < n2; j++)
        R[j] = cols[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            cols[k] = L[i];
            BeginDrawing();
            drawCols(cols, colCount, k, -1);
            EndDrawing();
            i++;
        }
        else {
            cols[k] = R[j];
            BeginDrawing();
            drawCols(cols, colCount, k, -1);
            EndDrawing();
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        cols[k] = L[i];
        BeginDrawing();
        drawCols(cols, colCount, k, -1);
        EndDrawing();
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        cols[k] = R[j];
        BeginDrawing();
        drawCols(cols, colCount, k, -1);
        EndDrawing();
        j++;
        k++;
    }
}

void mergeSort(double *cols, int l, int r, int colCount)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(cols, l, m, colCount);
        mergeSort(cols, m + 1, r, colCount);

        merge(cols, l, m, r, colCount);
    }
}

int partition(double *cols, int l, int h, int colCount) {
    
    // Choose the pivot
    int pivot = cols[h];
    
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = l - 1;

    // Traverse arr[low..high] and move all smaller
    // elements to the left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = l; j <= h - 1; j++) {
        if (cols[j] < pivot) {
            i++;
            swapCols(&cols[i], &cols[j]);
            BeginDrawing();
            drawCols(cols, colCount, i, j);
            EndDrawing();
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swapCols(&cols[i + 1], &cols[h]);  
    BeginDrawing();
    drawCols(cols, colCount, i + 1, h);
    EndDrawing();

    return i + 1;
}

void quickSort(double *cols, int low, int high, int colCount) {
    if (low < high) {
        
        // pi is the partition return index of pivot
        int pi = partition(cols, low, high, colCount);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(cols, low, pi - 1, colCount);
        quickSort(cols, pi + 1, high, colCount);
    }
}

void heapify(double *cols, int n, int i, int colCount) {

    // Initialize largest as root
    int largest = i; 

    // left index = 2*i + 1
    int l = 2 * i + 1; 

    // right index = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < n && cols[l] > cols[largest]) {
        largest = l;
    }

    // If right child is larger than largest so far
    if (r < n && cols[r] > cols[largest]) {
        largest = r;
    }

    // If largest is not root
    if (largest != i) {
        swapCols(&cols[i], &cols[largest]);

        BeginDrawing();
        drawCols(cols, colCount, i, largest);
        EndDrawing();

        // Recursively heapify the affected sub-tree
        heapify(cols, n, largest, colCount);
    }
}

void heapSort(double *cols, int colCount) {

    // Build heap (rearrange array)
    for (int i = colCount / 2 - 1; i >= 0; i--) {
        heapify(cols, colCount, i, colCount);
    }

    // One by one extract an element from heap
    for (int i = colCount - 1; i > 0; i--) {

        // Move current root to end
        int temp = cols[0]; 
        cols[0] = cols[i];
        cols[i] = temp;

        // Call max heapify on the reduced heap
        heapify(cols, i, 0, colCount);
    }
}

void cycleSort(double *cols, int colCount){    
    int start, pos, i;    
    double element;

   /*Loop to traverse the array elements and place them on the correct position*/  
    for (start = 0; start <= colCount - 2; start++) {    
        element = cols[start];  
          
        /*position to place the element*/  
        pos = start;    
          
        for (i = start + 1; i < colCount; i++){
            if (cols[i] < element){
                pos++;   
            }
        }    
                             
        /*if the element is at exact position*/  
        if (pos == start){
            continue;    
        }

        while (element == cols[pos]){
            pos += 1;  
        }    

        if (pos != start){    
            swapCols(&element, &cols[pos]);      

            BeginDrawing();
            drawCols(cols, colCount, pos, -1);
            EndDrawing();
        }    
        /*Rotate rest of the elements*/  
        while (pos != start)   {    
            pos = start;    
            /*find position to put the element*/  
            for (i = start + 1; i < colCount; i++){
                if (cols[i] < element){
                    pos += 1;  
                }
            }      
              
            /*Ignore duplicate elements*/  
            while (element == cols[pos]){
                pos += 1;    
            }
              
            /*put element to its correct position*/  
            if (element != cols[pos]){    
                swapCols(&element, &cols[pos]);  

                BeginDrawing();
                drawCols(cols, colCount, pos, -1); 
                EndDrawing();
            }    
        }    
    }    
     
 }   