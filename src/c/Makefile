
all: main_test_test

BENCH := bench.o

CC:=cc -Wall -g -O3

%.o: %.c Makefile
	$(CC) -o $@ -c $<

main_test: main_test.c $(BENCH)
	$(CC) -o $@ $< $(BENCH)

timing_experiment: timing_experiment.c Makefile
	cc -Wall -O3 timing_experiment.c -o $@

fmt:
	clang-format -i *.h *.c

main_test_test: main_test
	bash -c "time ./main_test"

all_tests: main_test timing_experiment
	bash -c "time ./timing_experiment"
	bash -c "time ./main_test"

.PHONY: all all_tests main_test_test fmt
