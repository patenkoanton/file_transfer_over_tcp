CC = g++
STD = c++14
CFLAGS = -Wall -g --std=$(STD)
SRC_DIR = src
APPS = \
	client \
	server \

TARGET_EXT = .out
TARGETS = $(addsuffix $(TARGET_EXT), $(APPS))

# both client and server depend on these modules
COMMON_DEPENDENCIES = $(addsuffix .o, \
	application \
	socket \
	ip_address \
)

.PHONY: all clean $(APPS)

all: $(APPS)

$(APPS): %: $(addsuffix $(TARGET_EXT), %)

$(TARGETS): $(addsuffix $(TARGET_EXT), %): %_main.o %.o $(COMMON_DEPENDENCIES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS)
	rm -f $(addsuffix .o, $(APPS))
	rm -f $(addsuffix _main.o, $(APPS))
	rm -f $(COMMON_DEPENDENCIES) 