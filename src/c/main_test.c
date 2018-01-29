// (C) 2017-2018 All Rights Reserved Laurent Demailly.

#include "bench.h"

#include <stdio.h>

// -- main/ test

#define N 5

void to_measure(void *ctx) {
    double *jptr = (double *)ctx;
    long i;
    for (i = 0; i < N; i++) {
        *jptr += i;
    }
}

#define ITERS (1000000000 / N)

int main() {
    double j = 0;
    run(to_measure, &j, "to_measure");
    long i;
    struct timespec delta;
    startClock();
    for (i = 0, j = 0; i < ITERS; ++i) {
        to_measure(&j);
    }
    endClock(&delta);
    LOG(INFO, printf("INF j=%g\n", j))
    printClock("loop", ITERS, &delta);
    return 0;
}
