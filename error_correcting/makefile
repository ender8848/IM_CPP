CC = g++ -g -Wall

main: correct.o main.o
	$(CC) correct.o main.o -o correct

main.o: main.cpp 
	$(CC) -c main.cpp 

correct.o: correct.cpp correct.h
	$(CC) -c correct.cpp 

tidy: 
	rm *.o

clean: 
	rm correct *.o