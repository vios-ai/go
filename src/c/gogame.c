// (C) 2017-2018 All Rights Reserved Laurent Demailly.

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "bench.h"

typedef struct {
    int n;
    int16_t *board;
} GoBoard;

// NewGoBoard creates a new board at requested size.
GoBoard NewGoBoard(int sz) {
    GoBoard res;
    res.n = sz;
    if (sz > 0) {
        res.board = calloc(sz * sz, sizeof(int16_t));
    } else {
        res.board = NULL;
    }
    return res;
}

// Copy1 clones the board.
void Copy1(GoBoard *dst, const GoBoard src) {
    size_t sz = src.n * src.n * sizeof(int16_t);
    if (dst->n != src.n) {
        dst->n = src.n;
        // no need to calloc as we're copying all the data
        if (dst->board == NULL) {
            dst->board = malloc(sz);
        } else {
            dst->board = realloc(dst->board, sz);
        }
    }
    memcpy(dst->board, src.board, sz);
}

GoBoard b19;
GoBoard b13;
GoBoard b9;

void test19(void *ctx) {
    Copy1(ctx, b19);
}
void test13(void *ctx) {
    Copy1(ctx, b13);
}
void test9(void *ctx) {
    Copy1(ctx, b9);
}

void testAlternate(void *ctx) {
  Copy1(ctx, b19);
  Copy1(ctx, b13);
}

void noop(void *ctx) {
    return;
}

int main() {
    b19 = NewGoBoard(19);
    b13 = NewGoBoard(13);
    b9 = NewGoBoard(9);
    GoBoard dst = NewGoBoard(0);
    run(noop, &dst, "noop");
    run(test19, &dst, "19 board, Copy1");
    run(test13, &dst, "13 board, Copy1");
    run(test9, &dst, "9 board, Copy1");
    run(testAlternate, &dst, "both 19/13 alternating, Copy1");
    return 0;
}
