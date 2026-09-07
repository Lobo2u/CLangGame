CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = clanggame
SRCS = main.c functions.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) functions.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
