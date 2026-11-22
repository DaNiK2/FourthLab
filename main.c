#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int * random_data(int size) {
    srand((unsigned int)time(NULL));
    int * res = malloc(sizeof(int) * size);
    if (!res) {
        printf("Memory allocation failed\n");
        return NULL;
    }
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
void quick_sort_counted(int * massive, int low, int high, unsigned long long * swap_count, unsigned long long *compare_count) {
    if (low >= high) {return;}
    int p = low + (high - low) / 2;
    int pivot = massive[p];
    int i = low, j = high;
    while (i <= j) {
        (*compare_count) ++;
        while (massive[i] < pivot) {
            (*compare_count)++;
            i++;
        }
        while (massive[j] > pivot) {
            (*compare_count)++;
            j--;
        }
        if (i <= j) {
            swap(i, j, massive);
            (*swap_count)++;
            i++;
            j--;
        }
    }
    quick_sort_counted(massive, low, j, swap_count, compare_count);
    quick_sort_counted(massive, i, high, swap_count, compare_count);
}

void quick_sort_bench(int * massive, int low, int high) {
    int * copy = malloc(sizeof(int) * (high - low + 1));
    if (!copy) {
        printf("Memory allocation failed\n");
        return;
    }
    for (int i = low; i <= high; i++) {
        copy[i] = massive[i];
    }
    printf("Quick sort timer: ");
    clock_t begin = clock();
    quick_sort(massive, low, high);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    unsigned long long swap_count = 0, compare_count = 0;
    quick_sort_counted(massive, low, high, &swap_count, &compare_count);
    printf("Count of permutation: %llu\n", swap_count);
    printf("Count of compare: %llu\n", compare_count);
}

int main() {
    int size = 0;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int * arr = random_data(size);
    quick_sort_bench(arr, 0, size - 1);
}