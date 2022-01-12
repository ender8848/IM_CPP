CC = g++ -g -Wall

laser: laser.o main.o
	$(CC) laser.o main.o -o laser

main.o: main.cpp laser.cpp
	$(CC) -c main.cpp 

laser.o: laser.cpp laser.h
	$(CC) -c laser.cpp 

tidy: 
	rm -rf *.o

clean: 
	rm -rf laser *.o