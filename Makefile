CC?=gcc

SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)

CFLAGS=-std=c99 -O2 -Wall
LIBS=-lSDL2
OUTPUT=tetris

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUTPUT) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm *.o
	rm $(OUTPUT)
