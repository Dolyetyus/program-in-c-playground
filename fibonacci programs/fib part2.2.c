#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int* numbers;
int size = 0;

//Oha amk bunu assemblyde nasil yapacaz

uint64_t fibonacci(int n) {
    if (n <= size) {
        return numbers[n - 1];
    } 
    else {
        int first = numbers[size - 2];
        int second = numbers[size - 1];
        int sum;

        while (size < n) {
            sum = first + second;
            first = second;
            second = sum;
            numbers = realloc(numbers, (size + 1) * sizeof(int));
            numbers[size] = second;
            size++;
        }

        for (int i = 0; i < size; i++) {
            printf("%d\n", numbers[i]);
        }

        return sum;
    }
}

int main() {
    int n, ret;

    while (1) {
        scanf("%d", &n);

        if (n == 0) {
            break;
        } 
        else if (n < 0) {
            continue;
        }

        numbers = (int*)malloc(2 * sizeof(int));
        numbers[0] = 1;
        numbers[1] = 1;
        size = 2;

        ret = fibonacci(n);
        printf("sum: %d\n", ret);

        free(numbers);
    }

    return 0;
}
