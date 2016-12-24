test_dirf:test_dirf.o
	gcc -o test_dirf test_dirf.c

PHONY:clean
clean:
	rm test_dirf.o test_dirf
