CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c scanner.c utils.c messages.c
OBJS = $(SRCS:.c=.o)
TARGET = zeroscan

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

