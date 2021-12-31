CC = g++ -g -Wall

main: gogen.o main.o
	$(CC) gogen.o main.o -o gogen

main.o: main.cpp 
	$(CC) -c main.cpp 

gogen.o: gogen.cpp gogen.h
	$(CC) -c gogen.cpp 

tidy: 
	rm *.o

clean: 
	rm gogen *.o