CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -O2 -g
SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)


.PHONY : clean

clean:
	rm -f bin/translator
