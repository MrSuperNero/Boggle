CC=gcc
CFLAGS= -pedantic -Wall -g3

all:    Boggle 

#####
# Instructions to make Boggle
#####

Boggle: Boggle.o trie.o error.o 
	${CC} ${CFLAGS} -o $@ $^

Boggle.o: trie.h error.h

trie.o: trie.h

clean:
	rm -f Boggle *.o
