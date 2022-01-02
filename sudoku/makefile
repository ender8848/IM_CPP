CC = g++ -g -Wall

main: sudoku.o main.o
	$(CC) sudoku.o main.o -o sudoku

main.o: main.cpp 
	$(CC) -c main.cpp 

sudoku.o: sudoku.cpp sudoku.h
	$(CC) -c sudoku.cpp 

tidy: 
	rm *.o

clean: 
	rm sudoku *.o