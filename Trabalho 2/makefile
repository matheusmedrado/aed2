CC = gcc
CFLAGS = -Wall -g

all: huffman_compression

huffman_compression: main_huffman.o huffman.o arvoreBinaria.o
	$(CC) $(CFLAGS) -o huffman_compression main_huffman.o huffman.o arvoreBinaria.o

main_huffman.o: main_huffman.c huffman.h
	$(CC) $(CFLAGS) -c main_huffman.c

huffman.o: huffman.c huffman.h arvoreBinaria.h
	$(CC) $(CFLAGS) -c huffman.c

arvoreBinaria.o: arvoreBinaria.c arvoreBinaria.h
	$(CC) $(CFLAGS) -c arvoreBinaria.c

clean:
	rm -f *.o huffman_compression
