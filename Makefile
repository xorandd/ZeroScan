CC = gcc
CFLAGS = -Wall -Wextra -g -pthread
TARGET = zeroscan
SRC = main.c scanner.c utils.c messages.c threading.c

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

