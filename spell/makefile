CC = g++ -g -Wall

spell: spell.o main.o
	$(CC) spell.o main.o -o spell

main.o: main.cpp 
	$(CC) -c main.cpp 

spell.o: spell.cpp spell.h
	$(CC) -c spell.cpp 

clean: 
	rm -rf spell *.o