// (C) 2017-2018 All Rights Reserved Laurent Demailly.

#include <time.h>

void startClock();
void endClock(struct timespec *res);
void printClock(char *msg, long n, const struct timespec *v);
double clockToUsec(const struct timespec *v);

// run() executes f(ctx) 1000 time to get an estimate of the time per run,
// then runs f(ctx) another N times such as it runs for about 5 seconds and a
// round power of 10 (e.g  600,000 times).
// prints results prefixed by msg.
void run(void (*f)(void *), void *ctx, char *msg);

// LogLevels
typedef enum {
    DEBUG,
    VERBOSE,
    INFO,
    WARNING,
    ERROR,
} LogLevels;

extern LogLevels _logLvl;

#define LOG(lvl, x)           \
    {                         \
        if (lvl >= _logLvl) { \
            x;                \
        }                     \
    }
