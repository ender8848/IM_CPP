CC = g++ -g -Wall

main: maze.o main.o
	$(CC) maze.o main.o -o maze

main.o: main.cpp 
	$(CC) -c main.cpp 

maze.o: maze.cpp maze.h
	$(CC) -c maze.cpp 

tidy: 
	rm *.o

clean: 
	rm maze *.o