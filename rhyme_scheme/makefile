CC = g++ -g -Wall

main: sonnet.o main.o
	$(CC) sonnet.o main.o -o sonnet

main.o: main.cpp 
	$(CC) -c main.cpp 

sonnet.o: sonnet.cpp sonnet.h
	$(CC) -c sonnet.cpp

tidy: 
	rm *.o

clean: 
	rm sonnet *.o