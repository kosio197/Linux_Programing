

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define TEST_SIZE 10000

void time_calloc() {
    time_t t = clock();
    int i;
    for (i = 0; i < TEST_SIZE; i++) {
        char* test = calloc(1, TEST_SIZE);
        int j;
        for (j = 0; j < TEST_SIZE; j++) {
            test[j] = rand() % 255;
        }
        free(test);
    }
    printf("Calloc time: %lf\n", (double) (clock() - t) / CLOCKS_PER_SEC);
}

void time_malloc() {
    time_t t = clock();
    int i;
    for (i = 0; i < TEST_SIZE; i++) {
        char* test = malloc(TEST_SIZE);
        int j;
        for (j = 0; j < TEST_SIZE; j++) {
            test[j] = rand() % 255;
        }
        free(test);
    }
    printf("Malloc time: %lf\n", (double) (clock() - t) / CLOCKS_PER_SEC);
}

void time_realloc() {
    time_t t = clock();
    char* test = malloc(TEST_SIZE);

    int i;
    for (i = 0; i < TEST_SIZE; i++) {
        test = realloc(test, TEST_SIZE);
        int j;
        for (j = 0; j < TEST_SIZE; j++) {
            test[j] = rand() % 255;
        }
    }

    free(test);
    printf("Realloc time: %lf\n", (double) (clock() - t) / CLOCKS_PER_SEC);
}

int main(int argc, char** argv) {

    time_malloc();
    time_calloc();
    time_realloc();

    return (EXIT_SUCCESS);
}

