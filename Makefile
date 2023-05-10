CC=g++
CFLAGS=-I.

CPP_FILES := $(wildcard *.cpp)

client: ${CPP_FILES}
	$(CC) -o client ${CPP_FILES} -Wall

run: client
	./client

clean:
	rm -f *.o client
