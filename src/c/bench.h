// (C) 2017-2018 All Rights Reserved Laurent Demailly.

#include <time.h>

void startClock();
void endClock(struct timespec *res);
void printClock(char *msg, long n, const struct timespec *v);
double clockToUsec(const struct timespec *v);

void run(void (*f)(void *), void *ctx, char *msg);
