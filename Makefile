CC=g++ -ggdb3 -std=c++11
CFLAGS=-I.

CPP_FILES := $(wildcard *.cpp)

client: ${CPP_FILES}
	$(CC) -o client ${CPP_FILES} -Wall

run: client
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./client

clean:
	rm -f *.o client valgrind-out.txt
