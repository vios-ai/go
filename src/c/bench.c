// (C) 2017-2018 All Rights Reserved Laurent Demailly.

#include "bench.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// file local
struct timespec timer;

#define CLOCK_ID CLOCK_THREAD_CPUTIME_ID

void startClock() {
    if (clock_gettime(CLOCK_ID, &timer)) {
        perror("clock_gettime");
        exit(1);
    }
}

void endClock(struct timespec *res) {
    struct timespec now;
    clock_gettime(CLOCK_ID, &now);
    res->tv_sec = now.tv_sec - timer.tv_sec;
    res->tv_nsec = now.tv_nsec - timer.tv_nsec;
    timer = now;
}

double clockToUsec(const struct timespec *v) {
    double usec = 1e6 * v->tv_sec;
    usec += 1e-3 * v->tv_nsec;
    return usec;
}

void printClock(char *msg, long n, const struct timespec *v) {
    double usec = clockToUsec(v);
    usec /= (double)n;
    printf("%s:\t%ld\t %.03f usec/op\n", msg, n, usec);
}

void run(void (*f)(void *), void *ctx, char *msg) {
    struct timespec delta;
    startClock();
    (*f)(ctx);
    endClock(&delta);
    double usec = clockToUsec(&delta);
    printClock(msg, 1, &delta);
    if (delta.tv_sec >= 5) {
        return;
    }
    double iters = 5e6 / usec;  // target to take about 5s
    double power = pow(10, floor(log10(iters)));
    long n = (long)(power * round(iters / power));
    printf("%g -> %ld (%g)\n", iters, n, power);
}
