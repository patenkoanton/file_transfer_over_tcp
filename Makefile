CC = g++
STD = c++14
CFLAGS = -Wall -g --std=$(STD)
SRC_DIR = src

SERVER_APP = server.out
SERVER_OBJ = \
	server_main.o \
	server.o \

CLIENT_APP = client.out
CLIENT_OBJ = \
	client_main.o \
	client.o \

.PHONY: all client server clean

all: client server

client: $(CLIENT_APP)
server: $(SERVER_APP)

$(CLIENT_APP): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER_APP): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CLIENT_APP) $(SERVER_APP) $(CLIENT_OBJ) $(SERVER_OBJ)