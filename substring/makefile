CC = g++ -g -Wall

substring: substring.o main.o
	$(CC) substring.o main.o -o substring

main.o: main.cpp 
	$(CC) -c main.cpp 

substring.o: substring.cpp substring.h
	$(CC) -c substring.cpp 

clean: 
	rm substring *.o