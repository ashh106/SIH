#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Testing Bubble Sort
    printf("Original array: \n");
    printArray(arr, n);

    bubbleSort(arr, n);
    printf("Sorted array using Bubble Sort: \n");
    printArray(arr, n);

    // Reset the array for testing Insertion Sort
    int arr2[] = {64, 25, 12, 22, 11};
    insertionSort(arr2, n);
    printf("Sorted array using Insertion Sort: \n");
    printArray(arr2, n);

    // Reset the array for testing Selection Sort
    int arr3[] = {64, 25, 12, 22, 11};
    selectionSort(arr3, n);
    printf("Sorted array using Selection Sort: \n");
    printArray(arr3, n);

    return 0;
}
