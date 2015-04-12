#include "sort.hpp"
#include <stdio.h>

void printArray(int arr[], size_t len) {
    printf("Array:");
    for (int i = 0; i < len; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void printArr(int *p, size_t len) {
    printf("Array:");
    for (int i = 0; i < len; i++) {
        printf("%d", *(p + i));
    }
    printf("\n");
}

/*
 * Worst case complexity is O(n^2)
 * When the array is already sorted the complexity is O(n)
 */
int* bubble_sort (int arr[], size_t len) {
    // keep track of the passes over the array, starting with one. O(n)
    for (int i = 1; i < len; i++) {
        bool swapped = false;
        // first pass N-1 comparisions, second pass N-2 comparisions...N*(N-1)/2. 5*(5-1)/2 = 20/2 = 10
        for (int j = 0; j < len - i; j++) {
            int next = j+1;
            if (arr[j] > arr[next]) {
                int tmp = arr[j];
                arr[j] = arr[next];
                arr[next] = tmp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return arr;
}

int* insertion_sort (int arr[], size_t len) {
    // keep track of the passes over the array, starting with one. O(n)
    for (int i = 1; i < len; i++) {
        // j is our "marker" for the already sorted items. 
        // On the first pass we are comparing the current item 'i'.
        // On the next passes we are checking if any of the already sorted items need swapping.
        for (int j = i; j > 0 && arr[j] < arr[j-1];j--) {
            int tmp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = tmp;
        }
    }
    return arr;
}

