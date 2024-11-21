CC=g++
CFLAGS= -c -g -Wall -std=c++17 -fpermissive
EXENAME= AVL

default: main.o
	$(CC) main.o -o $(EXENAME)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm *.o $(EXENAME)

run:
	./$(EXENAME)

