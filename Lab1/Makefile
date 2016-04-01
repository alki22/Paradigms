TARGET = dictionary
CC = gcc
CFLAGS = -g
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

.all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

-include .depend

.depend: $(SOURCES) $(HEADERS) 
	$(CC) -MM $(SOURCES) > .depend
clean:
	rm -f $(TARGET) $(OBJECTS)
