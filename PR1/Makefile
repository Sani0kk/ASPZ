CC = gcc
CFLAGS = -g -O2
LDFLAGS = -L/usr/lib -lprocess1 -L~/mylibs -lprocess
OBJ = main.o input.o output.o
TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

main.o: main.c input.h output.h process1.h process.h
	$(CC) $(CFLAGS) -c main.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

output.o: output.c output.h
	$(CC) $(CFLAGS) -c output.c

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
