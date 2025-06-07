CC=gcc
CFLAGS=-Wall -O2 -g
LIBDIRS=-L/usr/lib -L/home/sani0kk/mylibs
LIBS=-lprocess1 -lprocess

OBJS=input.o output.o

all: my_program

my_program: main.c $(OBJS)
	$(CC) $(CFLAGS) main.c $(OBJS) $(LIBDIRS) $(LIBS) -o my_program

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o my_program