CC = g++ -g -Wall

main: substring.o main.o
	$(CC) substring.o main.o -o main

main.o: main.cpp 
	$(CC) -c main.cpp 

substring.o: substring.cpp substring.h
	$(CC) -c substring.cpp 

clean: 
	rm main *.o