CC = g++ -g -Wall

tube: tube.o main.o
	$(CC) tube.o main.o -o tube

main.o: main.cpp 
	$(CC) -c main.cpp 

tube.o: tube.cpp tube.h
	$(CC) -c tube.cpp 

tidy: 
	rm *.o

clean: 
	rm tube *.o