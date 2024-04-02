#include <stdio.h>
#include <time.h>

int main() {
    long num1 = 10, num2 = 5;
    long add, subtract, multiply;
    float divide;

    time_t start, end;
    double cpu_time_used;

    start = clock();
    for (long i = 0; i < 1000000000; i++){
        add = num1 + num2;
        subtract = num1 - num2;
        multiply = num1 * num2;
        divide = num1 / (float)num2;
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken to perform operations: %f seconds\n", cpu_time_used);

    return 0;
}
