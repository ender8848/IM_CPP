CC = g++ -g -Wall

main: playfair.o main.o
	$(CC) playfair.o main.o -o playfair

main.o: main.cpp 
	$(CC) -c main.cpp 

playfair.o: playfair.cpp playfair.h
	$(CC) -c playfair.cpp 

tidy: 
	rm *.o

clean: 
	rm playfair *.o