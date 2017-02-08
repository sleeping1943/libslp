all:test_create_server

.PHONY : test_create_server

test_create_server:./src/test_create_server.cpp
	g++ -g -o $@ $^ -lshelper -llua

clean:
	@rm -f test_create_server
	@rm -f ./src/*.o
	@make  clean -C ./read
	@make  clean -C ./write

