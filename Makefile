
main: main.o
	g++ main.o -std=c++14 -O0 -o main

main.o: main.cpp
	g++ -std=c++14 -O0 -pedantic -Wall -g -c main.cpp -o main.o

clean:
	rm *.o
