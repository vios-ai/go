// (C) 2017-2018 All Rights Reserved Laurent Demailly.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>

// -- CLOCK_ID() way
clock_t t;

void startTimer() {
    t = CLOCK_ID();
}

clock_t endTimer() {
    clock_t n = CLOCK_ID();
    clock_t elapsed = n - t;
    t = n;
    return elapsed;
}

void printTimer(char *msg, clock_t v) {
    printf("%s: %lu clicks (%f us)\n", msg, v,
           1000000. * ((double)v) / CLOCKS_PER_SEC);
}

// -- rusage way

struct rusage usage;

void startUsage() {
    memset(&usage, 0, sizeof(usage));
    if (getrusage(RUSAGE_SELF, &usage)) {
        perror("getrusage");
        exit(1);
    }
}

void endUsage(struct rusage *delta) {
    struct rusage tempu;
    memset(&tempu, 0, sizeof(tempu));
    if (getrusage(RUSAGE_SELF, &tempu)) {
        perror("getrusage");
        exit(1);
    }
    long *ptrNew = (long *)&tempu;
    long *ptrPrv = (long *)&usage;
    long *ptrRes = (long *)delta;
    // substract all fields as long (usec is actually int32 but padded)
    printf("tv_usec sz = %lu vs %lu\n", sizeof(tempu.ru_utime.tv_usec),
           sizeof(long));
    assert(sizeof(tempu.ru_utime) == 2 * sizeof(long));
    for (int i = 0;
         ((char *)ptrNew) <= ((char *)&tempu) + sizeof(tempu) - sizeof(long);
         i++) {
        long diff = (*ptrNew) - (*ptrPrv);
        printf("%d: now %ld delta -> %ld\n", i, *ptrNew, diff);
        *(ptrRes++) = diff;
        *(ptrPrv++) = *(ptrNew++);
    }
}

// TODO: printUsage()

// -- http://man7.org/linux/man-pages/man2/clock_gettime.2.html way

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

void printClock(char *msg, const struct timespec *v) {
    int64_t ns = v->tv_nsec;
    int64_t us = ns / 1000;
    ns -= 1000 * us;
    int64_t ms = us / 1000;
    us -= 1000 * ms;
    printf("%s: %lu seconds %lld ms %lld us %lld ns\n", msg, v->tv_sec, ms, us,
           ns);
}

// -- main/ test

#define N 50000

double to_measure() {
    long i;
    double j;
    for (i = 0, j = 0; i < N; i++) {
        j += i;
    }
    return j;
}

int main() {
    int i;
    double j;
    struct rusage delta;
    struct timespec delta2;
    clock_t v;
    /*
      printf("timeval sz = %lu - %lu\n", sizeof(struct timeval), sizeof(long));
      clock_t v;
      struct timespec delta2;
      // warmup
      startTimer();
      for (i = 0, j = 0; i < N; i++) {
          j += i;
      }
      v = endTimer();
      printTimer("loop1", v);
      printf("j=%d\n", j);  // so the loop doesn't get optimized away
      startTimer();
      for (i = 0, j = 0; i < N; i++) {
          j += i;
      }
      v = endTimer();
      printTimer("loop2", v);
      printf("j=%d\n", j);  // so the loop doesn't get optimized away
    */
    startUsage();
    startTimer();
    startClock();
    for (i = 0, j = 0; i < N; i++) {
        j += to_measure();
    }
    v = endTimer();
    endClock(&delta2);
    printf("j=%f - ", j);  // so the loop doesn't get optimized away
    endUsage(&delta);
    printTimer("loop", v);
    printClock("loop", &delta2);
    printf("end - clocks per sec %d\n", CLOCKS_PER_SEC);
    return 0;
}
