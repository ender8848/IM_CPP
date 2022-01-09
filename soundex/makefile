CC = g++ -g -Wall

soundex: soundex.o main.o
	$(CC) soundex.o main.o -o soundex

main.o: main.cpp 
	$(CC) -c main.cpp 

soundex.o: soundex.cpp soundex.h
	$(CC) -c soundex.cpp 

clean: 
	rm -rf soundex *.o