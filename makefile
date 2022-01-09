CC = g++ -g -Wall

helpers: helpers.cpp
	$(CC) helpers.cpp -o helpers

clean: 
	rm -rf helpers