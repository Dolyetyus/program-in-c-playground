#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define ARRAY_SIZE 7500000
#define SCALAR 3.0
#define NUM_TRIALS 20

void init_arrays(double *a, double *b, double *c) {
    for (long i = 0; i < ARRAY_SIZE; i++) {
        a[i] = 1.0;
        b[i] = 2.0;
        c[i] = 0.0;
    }
}

void copy(double *a, double *c) {
    for (long i = 0; i < ARRAY_SIZE; i++) {
        c[i] = a[i];
    }
}

void scale(double *b, double *c) {
    for (long i = 0; i < ARRAY_SIZE; i++) {
        b[i] = SCALAR * c[i];
    }
}

void add(double *a, double *b, double *c) {
    for (long i = 0; i < ARRAY_SIZE; i++) {
        c[i] = a[i] + b[i];
    }
}

void triad(double *a, double *b, double *c) {
    for (long i = 0; i < ARRAY_SIZE; i++) {
        a[i] = b[i] + SCALAR * c[i];
    }
}

void execute(double *a, double *b, double *c) {
    double min_time[4];
    double max_time[4];
    double avg_time[4];
    double best_rate[4];
    int functions = 4;

    for (int i = 0; i < functions; i++) {
        min_time[i] = DBL_MAX;
        max_time[i] = 0.0;
        avg_time[i] = 0.0;
    }

    for (int i = 0; i < NUM_TRIALS; i++) {
        // Copy
        clock_t start = clock();
        copy(a, c);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        avg_time[0] += time_spent;
        if (time_spent < min_time[0]) min_time[0] = time_spent;
        if (time_spent > max_time[0]) max_time[0] = time_spent;

        // Scale
        start = clock();
        scale(b, c);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        avg_time[1] += time_spent;
        if (time_spent < min_time[1]) min_time[1] = time_spent;
        if (time_spent > max_time[1]) max_time[1] = time_spent;

        // Add
        start = clock();
        add(a, b, c);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        avg_time[2] += time_spent;
        if (time_spent < min_time[2]) min_time[2] = time_spent;
        if (time_spent > max_time[2]) max_time[2] = time_spent;

        // Triad
        start = clock();
        triad(a, b, c);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        avg_time[3] += time_spent;

        if (time_spent < min_time[3]) {
            min_time[3] = time_spent;
        }
        if (time_spent > max_time[3]) {
            max_time[3] = time_spent;
        }
    }

    for (int i = 0; i < functions; i++) {
        avg_time[i] /= NUM_TRIALS;
        double bytes_transferred = (i >= 2) ? 3 * ARRAY_SIZE * sizeof(double) : 2 * ARRAY_SIZE * sizeof(double);
        best_rate[i] = bytes_transferred / (min_time[i] * 1e6);
    }

    printf("Copy:     %11.1f     %f     %f     %f\n", best_rate[0], avg_time[0], min_time[0], max_time[0]);
    printf("Scale:    %11.1f     %f     %f     %f\n", best_rate[1], avg_time[1], min_time[1], max_time[1]);
    printf("Add:      %11.1f     %f     %f     %f\n", best_rate[2], avg_time[2], min_time[2], max_time[2]);
    printf("Triad:    %11.1f     %f     %f     %f\n", best_rate[3], avg_time[3], min_time[3], max_time[3]);
}

int main() {
    double *a, *b, *c;

    a = (double*)malloc(ARRAY_SIZE * sizeof(double));
    b = (double*)malloc(ARRAY_SIZE * sizeof(double));
    c = (double*)malloc(ARRAY_SIZE * sizeof(double));

    init_arrays(a, b, c);

    printf("Array size = %ld (elements).\n", ARRAY_SIZE);
    printf("Each kernel will be executed %d times.\n", NUM_TRIALS);
    printf("---------------------------------------------------------------\n");
    printf("Function  Best Rate MB/s     Avg time     Min time     Max time\n");

    execute(a, b, c);

    free(a);
    free(b);
    free(c);

    return 0;
}
