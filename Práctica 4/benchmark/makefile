CC=g++
CFLAGS=-I./include

bin/Bench: object/main.o object/benchmark.o
	$(CC) -o bin/Bench $(CFLAGS) object/main.o object/benchmark.o -fopenmp

object/main.o: src/main.cpp
	$(CC) -c -o object/main.o $(CFLAGS) src/main.cpp -fopenmp

object/benchmark.o: src/benchmark.cpp
	$(CC) -c -o object/benchmark.o $(CFLAGS) src/benchmark.cpp -fopenmp

clean:
	rm object/*.o
