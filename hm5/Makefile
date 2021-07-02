all: ParallelCalculator

ParallelCalculator: main.o ParallelCalculator.o
	g++ -pthread main.o ParallelCalculator.o -o ParallelCalculator
	
main.o: main.cpp ParallelCalculator.h
	g++ -c main.cpp -o main.o

ParallelCalculator.o: ParallelCalculator.cpp
	g++ -c ParallelCalculator.cpp

clean:
	rm *.o ParallelCalculator