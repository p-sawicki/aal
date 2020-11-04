CC=g++

dp.o: dp.h dp.cpp
	$(CC) -c dp.cpp -o dp.o

tests.o: tests.cpp dp.h
	$(CC) -c tests.cpp -o tests.o

tests: dp.o tests.o
	$(CC) tests.o dp.o -o tests

.PHONY: clean
clean:
	rm -rf *.o tests