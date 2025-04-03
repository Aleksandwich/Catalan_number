CC=gcc
CFLAGS=-Wall -Wextra
DEPS=fonction_catalan.h fonction_parenthese.h
OBJ=fonction_catalan.o fonction_parenthese.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

parentheses: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o parentheses