CC = g++ -g -Wall

main: minesweeper.o main.o
	$(CC) minesweeper.o main.o -o minesweeper

main.o: main.cpp 
	$(CC) -c main.cpp 

minesweeper.o: minesweeper.cpp minesweeper.h
	$(CC) -c minesweeper.cpp 

tidy: 
	rm *.o

clean: 
	rm minesweeper *.o