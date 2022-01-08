CC = g++ -g -Wall

main: scrabble.o main.o
	$(CC) scrabble.o main.o -o scrabble

main.o: main.cpp 
	$(CC) -c main.cpp 

scrabble.o: scrabble.cpp scrabble.h
	$(CC) -c scrabble.cpp 

tidy: 
	rm *.o

clean: 
	rm scrabble *.o