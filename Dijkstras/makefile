CC = gcc
CFLAGS = -Iinclude -O2
LDFLAGS = -lraylib -lm -lpthread -ldl -lGL -lrt -lX11

SRC_DIR = src
TARGET = game

SRCS = $(shell find $(SRC_DIR) -name '*.c')

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

