CC=g++
CFLAGS=-I.

UTILS_FILES := $(wildcard ./utils/*.cpp)

client: client.cpp ${UTILS_FILES}
	$(CC) -o client client.cpp ${UTILS_FILES} -Wall

run: client
	./client

clean:
	rm -f *.o client
