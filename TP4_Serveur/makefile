CC=gcc
FLAGS= -I/usr/include/mysql -lpthread -lmysqlclient

all: server

server: main.c
	$(CC) $< -o $@ $(FLAGS)
	
clean:
	rm -rf *~

mrproper: clean
	rm -rf server
