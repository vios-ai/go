// (C) 2017-2018 All Rights Reserved Laurent Demailly.

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>

clock_t t;

void startTimer() {
    t = clock();
}

clock_t endTimer() {
    clock_t n = clock();
    clock_t elapsed = n - t;
    t = n;
    return elapsed;
}

struct rusage usage;

void startUsage() {
    if (getrusage(RUSAGE_SELF, &usage)) {
        perror("getrusage");
        exit(1);
    }
}

void endUsage(struct rusage *delta) {
    struct rusage tempu;
    if (getrusage(RUSAGE_SELF, &tempu)) {
        perror("getrusage");
        exit(1);
    }
    long *ptrNew = (long *)&tempu;
    long *ptrPrv = (long *)&usage;
    long *ptrRes = (long *)delta;
    // substract all fields as long
    for (int i = 0;
         ((char *)ptrNew) <= ((char *)&tempu) + sizeof(tempu) - sizeof(long);
         i++) {
        long diff = (*ptrNew) - (*ptrPrv);
        printf("%d: %ld\n", i, diff);
        *(ptrRes++) = diff;
        *(ptrPrv++) = *(ptrNew++);
    }
}

void printTimer(char *msg, clock_t v) {
    printf("%s: %lu clicks (%f us)\n", msg, v,
           1000000. * ((double)v) / CLOCKS_PER_SEC);
}

int main() {
    printf("timeval sz = %lu - %lu\n", sizeof(struct timeval), sizeof(long));
    clock_t v;
    struct rusage delta;
    startTimer();
    v = endTimer();
    printTimer("no op", v);
    startUsage();
    endUsage(&delta);
    printf("end - clocks per sec %d\n", CLOCKS_PER_SEC);
    return 0;
}
