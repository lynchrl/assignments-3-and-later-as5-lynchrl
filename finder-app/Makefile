# Makefile for the "writer" program.

# CROSS_COMPILE is the prefix for the cross-compilation tools. This defaults to
# empty to use the native compiler.
CROSS_COMPILE ?=

all: writer

writer: writer.o
	$(CC) $(LDFLAGS) -o writer writer.o

writer.o: writer.c
	$(CC) $(CCFLAGS) -c writer.c

clean:
	rm -f writer writer.o