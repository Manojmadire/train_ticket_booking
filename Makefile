CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -g
TARGET = myirctc
SOURCES = main.c utils.c auth.c trains.c booking.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)
%.o: %.c common.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET)
run: $(TARGET)
	./$(TARGET)
.PHONY: all clean run
