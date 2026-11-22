#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int * random_data(int size) {
    srand((unsigned int)time(NULL));
    int * res = malloc(sizeof(int) * size);
    for (int i =0; i < size; i++) {
        res[i] = rand();
    }
    return res;
}

void swap(int first, int second, int* result) {
    int temp = result[second];
    result[second] = result[first];
    result[first] = temp;
}

int tester(int * massive, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (massive[i] > massive[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void quick_sort(int * massive, int low, int high) {
    if (low >= high) {return;}
    int p = low + (high - low) / 2;
    int pivot = massive[p];
    int i = low, j = high;
    while (i <= j) {
        while (massive[i] < pivot) {i++;}
        while (massive[j] > pivot) {j--;}
        if (i <= j) {
            swap(i, j, massive);
            i++;
            j--;
        }
    }
    quick_sort(massive, low, j);
    quick_sort(massive, i, high);
}

void quick_sort_timer(int * massive, int low, int high) {
    printf("Quick sort timer: ");
    clock_t begin = clock();
    quick_sort(massive, low, high);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
}

int main() {
    int size = 0;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int * arr = random_data(size);
    quick_sort_timer(arr, 0, size - 1);
}