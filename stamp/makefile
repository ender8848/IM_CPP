CC = g++ -g -Wall

main: stamp.o main.o
	$(CC) stamp.o main.o -o stamp -lcrypto

main.o: main.cpp 
	$(CC) -c main.cpp 

stamp.o: stamp.cpp stamp.h
	$(CC) -c stamp.cpp 

tidy: 
	rm *.o

clean: 
	rm stamp *.o