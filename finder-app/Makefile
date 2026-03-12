# Makefile for the "writer" program.

# CROSS_COMPILE is the prefix for the cross-compilation tools. This defaults to
# empty to use the native compiler.
CROSS_COMPILE ?=

all: writer

writer: writer.o
	$(CROSS_COMPILE)gcc -o writer writer.o

writer.o: writer.c
	$(CROSS_COMPILE)gcc -c writer.c

clean:
	rm -f writer writer.o