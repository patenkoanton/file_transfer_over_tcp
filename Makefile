CC = g++
STD = c++14
CFLAGS = -Wall -g --std=$(STD)
SRC_DIR = src

SERVER_APP = server.out
SERVER_MODULES =  \
	server_main \
	server \

CLIENT_APP = client.out
CLIENT_MODULES = \
	client_main \
	client \

# both client and server depend on these modules
COMMON_DEPENDENCIES = \
	application \
	socket \
	ip_address \

SERVER_OBJ = $(SERVER_MODULES:=.o)
CLIENT_OBJ = $(CLIENT_MODULES:=.o)
COMMON_DEPENDENCIES_OBJ = $(COMMON_DEPENDENCIES:=.o)

.PHONY: all client server clean

all: client server

client: $(CLIENT_APP)
server: $(SERVER_APP)

$(CLIENT_APP): $(CLIENT_OBJ) $(COMMON_DEPENDENCIES_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER_APP): $(SERVER_OBJ) $(COMMON_DEPENDENCIES_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CLIENT_APP) $(SERVER_APP) $(CLIENT_OBJ) $(SERVER_OBJ) $(COMMON_DEPENDENCIES_OBJ)