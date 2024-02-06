#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int* numbers;
int size = 0;

//Oha amk bunu assemblyde nasil yapacaz

uint64_t* fibonacci(int n, int curr_max, uint64_t* addr) {
    uint64_t* result;

    if (n <= curr_max) {
        result = addr;
    } 
    else {
        int size = curr_max;
        int first = addr[size - 2];
        int second = addr[size - 1];
        int sum;

        while (size < n) {
            sum = first + second;
            first = second;
            second = sum;
            addr = realloc(addr, (size + 1) * sizeof(uint64_t));
            addr[size] = second;
            size++;
        }

        result = addr;
    }

    return result;
}

int main() {
    int n;
    uint64_t* result;

    while (1) {
        scanf("%d", &n);

        if (n == 0) {
            break;
        } 
        else if (n < 0) {
            continue;
        }

        uint64_t* numbers = (uint64_t*)malloc(2 * sizeof(uint64_t));
        numbers[0] = 1;
        numbers[1] = 1;

        result = fibonacci(n, 2, numbers);

        for (int i = 0; i < n; i++) {
            printf("%lu\n", result[i]);
        }

        free(numbers);
    }

    return 0;
}
