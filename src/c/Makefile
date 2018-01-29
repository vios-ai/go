gogame: gogame.c Makefile
	cc -Wall -O3 gogame.c   -o gogame

fmt:
	clang-format -i gogame.c

test: gogame
	bash -c "time ./gogame"
