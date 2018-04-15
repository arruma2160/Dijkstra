CFLAG = -Wall -Wundef -ggdb -std=c++11
CC = g++
INCLUDE =
LIBS = 

main: elements.hpp main.cpp tests
	$(CC) $(CFLAG) main.cpp -o main

clean:
	rm -rf *.o ./test/test_build main

tests: 
	@cd ./test;\
	mkdir -p test_build;\
	cd test_build;\
	cmake .. && make && ./test
	
.PHONY: tests
