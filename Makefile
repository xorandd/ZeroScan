CFLAGS = -Wall -Wextra -g -pthread -O2
TARGET = zeroscan
SRC = src/main.c src/scanner.c src/utils.c src/messages.c src/threading.c

all:
	gcc $(CFLAGS) -o $(TARGET) $(SRC)
clean:
	@rm -v zeroscan
