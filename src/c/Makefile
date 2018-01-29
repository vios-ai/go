
all: test

BENCH := bench.o

CC:=cc -Wall -O3

%.o: %.c
	$(CC) -o $@ -c $<

main_test: main_test.c $(BENCH)
	$(CC) -o $@ $< $(BENCH)

timing_experiment: timing_experiment.c Makefile
	cc -Wall -O3 timing_experiment.c -o $@

fmt:
	clang-format -i *.h *.c

test: main_test timing_experiment
	bash -c "time ./timing_experiment"
	bash -c "time ./main_test"

.PHONY: all test fmt
