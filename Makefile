CC=gcc

TARGET=check_pid

SOURCES=$(wildcard *.c)

OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

INC:=

LIB:=

CFLAGS :=-D WHO_AM_I=\"$(TARGET)\" \
	-g

all: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) 
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INC) $(LIB)
.PHONY:clean
clean:
	-rm $(OBJECTS) $(TARGET)
