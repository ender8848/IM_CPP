CC = g++ -g -Wall

words: words.o main.o
	$(CC) words.o main.o -o words

main.o: main.cpp 
	$(CC) -c main.cpp 

words.o: words.cpp words.h
	$(CC) -c words.cpp 

tidy: 
	rm *.o

clean: 
	rm words *.o