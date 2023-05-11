CC=g++ -ggdb3 -std=c++11
CFLAGS=-I.

UTILS_FILES := $(wildcard ./utils/*.cpp)
CLASSES_FILES := $(wildcard ./classes/*.cpp)

client: client.cpp ${UTILS_FILES} ${CLASSES_FILES}
	$(CC) -o client client.cpp ${UTILS_FILES} -Wall

run: client
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./client

clean:
	rm -f *.o client valgrind-out.txt
