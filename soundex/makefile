CC = g++ -g -Wall

main: soundex.o main.o
	$(CC) soundex.o main.o -o main

main.o: main.cpp 
	$(CC) -c main.cpp 

soundex.o: soundex.cpp soundex.h
	$(CC) -c soundex.cpp 

clean: 
	rm main *.o