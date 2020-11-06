CC=g++
CFLAGS=-I inc -Wall --std=c++17 -O3

default: all
all: dp graph gen tests timer

# Dynamic-programming solution
dp.o: dp/dp.cpp
	$(CC) $(CFLAGS) -c dp/dp.cpp -o dp/dp.o
dp: dp/dp_main.cpp dp.o
	$(CC) $(CFLAGS) dp/dp.o dp/dp_main.cpp -o bin/dp

# Graph solution
graph.o: inc/graph.h graph/graph.cpp
	$(CC) $(CFLAGS) -c graph/graph.cpp -o graph/graph.o
graph: graph/graph_main.cpp graph.o
	$(CC) $(CFLAGS) graph/graph.o graph/graph_main.cpp -o bin/graph

# Tests generator
gen.o: inc/gen.h gen/gen.cpp
	$(CC) $(CFLAGS) -c gen/gen.cpp -o gen/gen.o
gen: gen/gen_main.cpp gen.o
	$(CC) $(CFLAGS) gen/gen_main.cpp gen/gen.o -o bin/gen

# Trivial tests suite
tests: tests.cpp dp.o gen.o
	$(CC) $(CFLAGS) tests.cpp dp/dp.o gen/gen.o -o bin/tests

# Auto-tests runner with timer
timer: timer.cpp gen.o dp.o
	$(CC) $(CFLAGS) timer.cpp gen/gen.o dp/dp.o -lpthread -o bin/timer

.PHONY: clean
clean:
	rm -f bin/* **/*.o
