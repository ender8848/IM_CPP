CC = g++ -g -Wall

main: river.o main.o
	$(CC) river.o main.o -o river

main.o: main.cpp 
	$(CC) -c main.cpp 

river.o: river.cpp river.h
	$(CC) -c river.cpp 

tidy: 
	rm *.o

clean: 
	rm river *.o