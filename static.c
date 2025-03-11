#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 20  // Reduced array size
#define THRESHOLD 3  // Threshold for static parallelism

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

void parallelMergeSortStatic(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        if ((right - left) < THRESHOLD) {  
            // If below threshold, use sequential sort
            parallelMergeSortStatic(arr, left, mid);
            parallelMergeSortStatic(arr, mid + 1, right);
        } else {
            // Static scheduling with OpenMP
            #pragma omp parallel
            {
                #pragma omp single nowait  // Ensure static division
                {
                    #pragma omp task
                    parallelMergeSortStatic(arr, left, mid);
                    #pragma omp task
                    parallelMergeSortStatic(arr, mid + 1, right);
                }
            }
        }
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
    srand(42);  // Seed for reproducibility

    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    printf("Original Array:\n");
    printArray(arr, N);

    double start = omp_get_wtime();
    parallelMergeSortStatic(arr, 0, N - 1);
    double end = omp_get_wtime();

    printf("Sorted Array:\n");
    printArray(arr, N);
    printf("Parallel Merge Sort (Static) Execution Time: %f seconds\n", end - start);

    return 0;
}
