#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint64_t* my_fib(uint64_t i, uint64_t **arr, uint64_t *size) {
    if (i < *size) {
        return *arr;
    }

    uint64_t *new_arr = realloc(*arr, (i + 1) * sizeof(uint64_t));

    *arr = new_arr;

    if (*size == 0) {
        new_arr[0] = 0;
        new_arr[1] = 1;
        *size = 2;
    }

    for (uint64_t idx = *size; idx <= i; ++idx) {
        new_arr[idx] = new_arr[idx - 1] + new_arr[idx - 2];
    }

    *size = i + 1;
    
    return new_arr;
}

int main() {
    uint64_t *arr = NULL;
    uint64_t size = 0;
    uint64_t i;

    while (1) {
        printf("Enter an index: ");
        if (scanf("%lu", &i) != 1) {
            printf("Exiting...\n");
            break;
        }

        uint64_t *fib_arr = my_fib(i, &arr, &size);

        printf("F_%lu = %lu\n", i, fib_arr[i]);
    }

    free(arr);

    return 0;
}
