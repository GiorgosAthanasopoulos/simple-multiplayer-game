all:client

CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++23 -g
LDFLAGS=-lenet -lraylib

BIN_DIR=bin

CLIENT_SRC=$(wildcard src/client/*.cpp)
CLIENT_EXEC=$(BIN_DIR)/client

SERVER_SRC=$(wildcard src/server/*.cpp)
SERVER_EXEC=$(BIN_DIR)/server

bin_dir:
	mkdir -p $(BIN_DIR)

server:bin_dir
	$(CC) $(CFLAGS) $(SERVER_SRC) -o $(SERVER_EXEC) $(LDFLAGS)
	./$(SERVER_EXEC)

client:bin_dir
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT_EXEC) $(LDFLAGS)
	./$(CLIENT_EXEC)
