all: client server master worker signal

client: client.c
	gcc -o client client.c

server: server.c
	gcc -o server server.c

master: server-master.c
	gcc -o master server-master.c

worker: server-worker.c
	gcc -o worker server-worker.c

signal: signal.c
	gcc -o signal signal.c
