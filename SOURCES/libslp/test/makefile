all:test_create_server

.PHONY : test_create_server

test_create_server:./src/test_create_server.cpp
	g++ -o $@ $^ -lslp_utils -llua

clean:
	rm -f test_create_server
	rm -f ./src/*.o

