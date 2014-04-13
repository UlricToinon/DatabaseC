CC=gcc
FLAGS=

all: client

client: main.c
	$(CC) $< -o $@ $(FLAGS)
	
clean:
	rm -rf *~

mrproper: clean
	rm -rf client
