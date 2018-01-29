timing_experiment: timing_experiment.c Makefile
	cc -Wall -O3 timing_experiment.c -o $@

fmt:
	clang-format -i timing_experiment.c

test: timing_experiment
	bash -c "time ./timing_experiment"
