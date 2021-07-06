all: Shell

Shell: main.o Shell.o
	g++ main.o Shell.o -o Shell
	
main.o: main.cpp Shell.h
	g++ -c main.cpp -o main.o

Shell.o: Shell.cpp
	g++ -c Shell.cpp

clean:
	rm *.o Shell
