CC=g++

dp.o: dp.h dp.cpp
	$(CC) -c dp.cpp -o dp.o

tests.o: tests.cpp
	$(CC) -c tests.cpp -o tests.o

main.o: dp_main.cpp
	$(CC) -c dp_main.cpp -o main.o

gen.o: gen.h gen.cpp
	$(CC) -c gen.cpp -o gen.o

gen_main.o: gen_main.cpp
	$(CC) -c gen_main.cpp -o gen_main.o

tests: dp.o tests.o gen.o
	$(CC) tests.o dp.o gen.o -o tests

dp: dp.o main.o
	$(CC) dp.o main.o -o dp

gen: gen_main.o gen.o
	$(CC) gen_main.o gen.o -o gen

timer: timer.cpp gen.o dp.o
	$(CC) timer.cpp gen.o dp.o -o timer -lpthread

.PHONY: clean
clean:
	rm -rf *.o tests dp gen timer