#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20  // Reduced array size

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void sequentialMergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[N];
    srand(time(0));

    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    printf("Original Array:\n");
    printArray(arr, N);

    clock_t start = clock();
    sequentialMergeSort(arr, 0, N - 1);
    clock_t end = clock();

    printf("Sorted Array:\n");
    printArray(arr, N);
    printf("Execution Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
