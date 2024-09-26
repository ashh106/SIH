#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>

void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);

int* generateRandomArray(int n);
void writeTimeToFile(FILE *fptr, int size, double bubble_time, double insertion_time, double selection_time);

int main() {
    int sizes[] = {100, 200, 500, 1000, 2000, 5000};  // Array sizes to test
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    FILE *fptr = fopen("time_data.txt", "w"); // File to store time data
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // Seed the random number generator
    srand(time(0));

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        int *arr = generateRandomArray(size);

        // Measure time for Bubble Sort
        int *arr_copy = (int*)malloc(size * sizeof(int));
        memcpy(arr_copy, arr, size * sizeof(int));
        clock_t start = clock();  // Start time for Bubble Sort
        bubbleSort(arr_copy, size);
        clock_t end = clock();    // End time for Bubble Sort
        double bubble_time = ((double)(end - start)) / CLOCKS_PER_SEC;  // Time difference in seconds
        free(arr_copy);

        // Measure time for Insertion Sort
        arr_copy = (int*)malloc(size * sizeof(int));
        memcpy(arr_copy, arr, size * sizeof(int));
        start = clock();  // Start time for Insertion Sort
        insertionSort(arr_copy, size);
        end = clock();    // End time for Insertion Sort
        double insertion_time = ((double)(end - start)) / CLOCKS_PER_SEC;  // Time difference in seconds
        free(arr_copy);

        // Measure time for Selection Sort
        arr_copy = (int*)malloc(size * sizeof(int));
        memcpy(arr_copy, arr, size * sizeof(int));
        start = clock();  // Start time for Selection Sort
        selectionSort(arr_copy, size);
        end = clock();    // End time for Selection Sort
        double selection_time = ((double)(end - start)) / CLOCKS_PER_SEC;  // Time difference in seconds
        free(arr_copy);

        // Write results to file
        writeTimeToFile(fptr, size, bubble_time, insertion_time, selection_time);

        free(arr);
    }

    fclose(fptr);
    printf("Time complexity data written to 'time_data.txt'.\n");
    return 0;
}

// Generate an array of random integers of size n
int* generateRandomArray(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;  // Random integers between 0 and 9999
    }
    return arr;
}

// Write array size and time taken by each algorithm to file
void writeTimeToFile(FILE *fptr, int size, double bubble_time, double insertion_time, double selection_time) {
    fprintf(fptr, "%d %lf %lf %lf\n", size, bubble_time, insertion_time, selection_time);
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}


// set title "Time Complexity of Sorting Algorithms"
// set xlabel "Array Size"
// set ylabel "Time (seconds)"
// set grid
// set key outside

// # Load the data file
// plot "time_data.txt" using 1:2 with linespoints title "Bubble Sort", \
//      "time_data.txt" using 1:3 with linespoints title "Insertion Sort", \
//      "time_data.txt" using 1:4 with linespoints title "Selection Sort"





// set terminal png
// set output "time_complexity.png"
// replot
// set terminal x11  # Reset the terminal to default for on-screen plotting
