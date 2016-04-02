CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)


bin/translator : $(OBJECTS)
	$(CC) $(CFLAGS) -o bin/translator $(OBJECTS)

src/main.o : src/main.c src/dict.h src/helpers.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/dict.o : src/dict.c src/dict.h src/bst.h src/helpers.h src/pair.h src/word.h
	$(CC) $(CFLAGS) -c src/dict.c -o src/dict.o

src/bst.o : src/bst.c src/bst.h src/stack.h src/pair.h src/word.h
	$(CC) $(CFLAGS) -c src/bst.c -o src/bst.o

src/helpers.o : src/helpers.c src/helpers.h
	$(CC) $(CFLAGS) -c src/helpers.c -o src/helpers.o

src/pair.o : src/pair.c src/pair.h src/word.h
	$(CC) $(CFLAGS) -c src/pair.c -o src/pair.o

src/stack.o : src/stack.c src/stack.h src/dict.h
	$(CC) $(CFLAGS) -c src/stack.c -o src/stack.o

src/word.o : src/word.h
	$(CC) $(CFLAGS) -c src/word.c -o src/word.o

valgrind : bin/translator
	valgrind --leak-check=full --show-reachable=yes bin/translator

.PHONY : clean

clean :
	rm -f bin/translator $(OBJECTS)
