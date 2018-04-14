CFLAG = -Wall -Wundef -ggdb -std=c++11
CC = g++
INCLUDE =
LIBS = 

all: tests

#main.o: main.cpp
#	$(CC) $(CFLAG) -c main.cpp

clean:
	rm -rf *.o ./test/test_build

tests: 
	@cd ./test;\
	mkdir -p test_build;\
	cd test_build;\
	cmake .. && make && ./dijkstra_tests
	
.PHONY: tests
