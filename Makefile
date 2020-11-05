CC=g++

dp.o: dp.h dp.cpp
	$(CC) -c dp.cpp -o dp.o

tests.o: tests.cpp dp.h
	$(CC) -c tests.cpp -o tests.o

main.o: dp_main.cpp dp.h
	$(CC) -c dp_main.cpp -o main.o

tests: dp.o tests.o
	$(CC) tests.o dp.o -o tests

main: dp.o main.o
	$(CC) dp.o main.o -o main

.PHONY: clean
clean:
	rm -rf *.o tests main