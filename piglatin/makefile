CC = g++ -g -Wall

main: piglatin.o main.o
	$(CC) piglatin.o main.o -o piglatin

main.o: main.cpp 
	$(CC) -c main.cpp 

piglatin.o: piglatin.cpp piglatin.h
	$(CC) -c piglatin.cpp 

tidy: 
	rm *.o

clean: 
	rm piglatin *.o