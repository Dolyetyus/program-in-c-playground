#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint64_t* my_fib(uint64_t i, uint64_t *arr, uint64_t size) {
    if (i < size) {
        return arr;
    }

    uint64_t *new_arr = realloc(arr, (i + 1) * sizeof(uint64_t));

    if (size < 2) {
        new_arr[0] = 0;
        new_arr[1] = 1;
        size = 2;
    }

    for (uint64_t idx = size; idx <= i; ++idx) {
        new_arr[idx] = new_arr[idx - 1] + new_arr[idx - 2];
    }

    return new_arr;
}

int main() {
    uint64_t size = 2;
    uint64_t *arr = arr = (uint64_t*)malloc(size * sizeof(uint64_t));
    arr[0] = 0;
    arr[1] = 1;
    
    uint64_t i;
    while (1) {
        printf("Enter an index: ");
        if (scanf("%lu", &i) != 1) {
            printf("Exiting...\n");
            break;
        }

        uint64_t *temp = my_fib(i, arr, size);
        
        arr = temp;
        size = i + 1;

        printf("F_%lu = %lu\n", i, arr[i]);
    }

    free(arr);

    return 0;
}
