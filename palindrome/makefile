CC = g++ -g -Wall

main: words.o main.o
	$(CC) words.o main.o -o main

main.o: main.cpp 
	$(CC) -c main.cpp 

words.o: words.cpp words.h
	$(CC) -c words.cpp 

tidy: 
	rm *.o

clean: 
	rm main *.o