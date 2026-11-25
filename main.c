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

int * copy_data(int * massive, int size) {
    int * result = malloc(sizeof(int) * size);
    if (!result) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        result[i] = massive[i];
    }
    return result;
}

void insert_sort(int * massive, int len) {
    for (int i = 1; i < len; i++) {
        int key = massive[i];
        int j = i - 1;
        while (j >= 0 && massive[j] > key) {
            massive[j + 1] = massive[j];
            j--;
        }
        massive[j + 1] = key;
    }
}

void insert_sort_counted(int * massive, int len, unsigned long long * swap_count, unsigned long long *compare_count) {
    for (int i = 1; i < len; i++) {
        int key = massive[i];
        int j = i - 1;
        while (j >= 0 && ((*compare_count)++, massive[j] > key)) {
            massive[j + 1] = massive[j];
            (*swap_count)++;
            j--;
        }
        if (j != i - 1) {
            massive[j + 1] = key;
            (*swap_count)++; // убери эту строку, если в вашей методичке считаются только сдвиги внутри цикла
        }
    }
}

void insert_sort_bench(int * massive, int size) {
    int * copy = copy_data(massive, size);
    printf("Insert sort timer: ");
    clock_t begin = clock();
    insert_sort(massive, size);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    unsigned long long swap_count = 0, compare_count = 0;
    insert_sort_counted(copy, size, &swap_count, &compare_count);
    printf("Count of permutation: %llu\n", swap_count);
    printf("Count of compare: %llu\n", compare_count);
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
    while ((*compare_count)++, i <= j) {
        while ((*compare_count)++, massive[i] < pivot) {
            i++;
        }
        while ((*compare_count)++, massive[j] > pivot) {
            (*compare_count)++;
            j--;
        }
        if ((*compare_count)++, i <= j) {
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
    int * copy = copy_data(massive, high - low + 1);
    printf("Quick sort timer: ");
    clock_t begin = clock();
    quick_sort(massive, low, high);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    unsigned long long swap_count = 0, compare_count = 0;
    quick_sort_counted(copy, low, high, &swap_count, &compare_count);
    printf("Count of permutation: %llu\n", swap_count);
    printf("Count of compare: %llu\n", compare_count);
}

int main() {
    int size = 0;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int * arr = random_data(size);
    int * arr_copy = copy_data(arr, size);
    quick_sort_bench(arr, 0, size - 1);
    free(arr);
    arr = copy_data(arr_copy, size);
    insert_sort_bench(arr, size);

}