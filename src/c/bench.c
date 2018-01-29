// (C) 2017-2018 All Rights Reserved Laurent Demailly.

#include "bench.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

LogLevels _logLvl = INFO;

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
    // 10th of nanosec max resolution
    printf("%s:\t%ld\t %.04f usec/op\t(%.3fs total)\n", msg, n, usec,
           n * usec / 1e6);
}

#define INITIAL_N 1000
void run(void (*f)(void *), void *ctx, char *msg) {
    struct timespec delta;
    startClock();
    for (int i = 0; i < INITIAL_N; ++i) {
        (*f)(ctx);
    }
    endClock(&delta);
    if (delta.tv_sec >= 2) {
        // took long enough for the short run, end here
        printClock(msg, INITIAL_N, &delta);
        return;
    }
    LOG(VERBOSE, printClock(msg, INITIAL_N, &delta))
    double usec = clockToUsec(&delta);
    double iters = 3e6 / usec * INITIAL_N;  // target to take about 3s
    double power = pow(10, floor(log10(iters)));
    long n = (long)(power * ceil(iters / power));
    LOG(DEBUG, printf("DBG 3s run would take %g iters -> %ld (p=%g)\n", iters,
                      n, power))
    startClock();
    for (int i = 0; i < n; ++i) {
        (*f)(ctx);
    }
    endClock(&delta);
    printClock(msg, n, &delta);
}
