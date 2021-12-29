CC = g++ -g -Wall

main: braille.o main.o
	$(CC) braille.o main.o -o main

main.o: main.cpp 
	$(CC) -c main.cpp 

braille.o: braille.cpp braille.h
	$(CC) -c braille.cpp 

tidy: 
	rm *.o

clean: 
	rm main *.o