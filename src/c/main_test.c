// (C) 2017-2018 All Rights Reserved Laurent Demailly.

#include "bench.h"

#include <stdio.h>

// -- main/ test

#define N 50000

double j;

void to_measure() {
    long i;
    for (i = 0, j = 0; i < N; i++) {
        j += i;
    }
}

int main() {
    j = 0;
    run(to_measure, NULL, "1 iter");
    int i;
    struct timespec delta;
    startClock();
    for (i = 0, j = 0; i < N; i++) {
        to_measure();
    }
    endClock(&delta);
    printf("j=%f - ", j);  // so the loop doesn't get optimized away
    printClock("loop", N, &delta);
    return 0;
}
