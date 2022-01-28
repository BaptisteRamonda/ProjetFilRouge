#Variables personnalisées
CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
EXEC=main

#Fichier qui regroupe l'ensemble des exécutables
all: $(EXEC)
	rm -rf *.o

main: main.o menu.o id.o
	$(CC) -o main main.o menu.o id.o $(LDFLAGS)


main.o: source/main.c
	$(CC) -o main.o -c source/main.c $(CFLAGS)

main.c: headers/menu.h headers/id.h


menu.o: source/menu.c
	$(CC) -o menu.o -c source/menu.c $(CFLAGS)

menu.c: headers/menu.h


id.o: source/id.c 
	$(CC) -o id.o -c source/id.c $(CFLAGS)

id.c: headers/id.h	