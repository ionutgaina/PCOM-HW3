CC=g++ -ggdb3 -std=c++11
CFLAGS=-I.

UTILS_FILES := $(wildcard ./utils/*.cpp)
CLASSES_FILES := $(wildcard ./classes/*.cpp)

client: client.cpp ${UTILS_FILES} ${CLASSES_FILES}
	$(CC) -o client client.cpp ${UTILS_FILES} -Wall

run: client
	./client

clean:
	rm -f *.o client valgrind-out.txt
