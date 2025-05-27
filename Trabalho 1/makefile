# Makefile para o projeto de Grafos

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
LDFLAGS = -lm

# Arquivos do projeto
SRCS = grafo.c main.c
OBJS = $(SRCS:.c=.o)
HEADERS = grafo.h
TARGET = analise_golfinhos

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test