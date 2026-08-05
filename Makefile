# CC like varible having value g++
CC = g++

app:Main.o CVFS.o
	$(CC) Main.cpp CVFS.o -o app

Main.o:
	$(CC) -c Main.cpp 

CVFS.o:
	$(CC) -c CVFS.cpp
        
clean:
	rm -f app *.o 

run:
	./app                  