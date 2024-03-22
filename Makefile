CC = gcc
CFLAGS = -Wall -Wextra

all: ForkCopy MyCopy PipeCopy

ForkCopy: ForkCopy.c
	$(CC) $(CFLAGS) -o ForkCopy ForkCopy.c

MyCopy: MyCopy.c
	$(CC) $(CFLAGS) -o MyCopy MyCopy.c

PipeCopy: PipeCopy.c
	$(CC) $(CFLAGS) -o PipeCopy PipeCopy.c

clean:
	rm -f ForkCopy MyCopy PipeCopy