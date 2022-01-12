CC = g++ -g -Wall -O3

doublets: doublets.o main.o
	$(CC) doublets.o main.o -o doublets

main.o: main.cpp 
	$(CC) -c main.cpp 

doublets.o: doublets.cpp doublets.h
	$(CC) -c doublets.cpp 

clean: 
	rm -rf doublets *.o