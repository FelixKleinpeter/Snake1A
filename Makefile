CSRC= snake.c shlanga.c min-max.c bonus.c menu.c file.c
CC = gcc
COBJ=$(CSRC:.c=.o)
CFLAGS = -O3 -Wall -Wswitch -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer


all: snake test_unitaires


mac: 
	gcc -o macbin $(CSRC) SDLMain.m -framework SDL -framework SDL_image -framework SDL_ttf -framework SDL_mixer -framework Cocoa -I/opt/SDL

snake: $(COBJ) main.o
	gcc -o snake $(COBJ) main.o $(CFLAGS)

test_unitaires: $(COBJ) test_unitaires.o
	gcc -o test_unitaires $(COBJ) test_unitaires.o $(CFLAGS)

snake.o: snake.c snake.h structures.h
	gcc -o snake.o -c snake.c $(CFLAGS)

shlanga.o: shlanga.c shlanga.h structures.h
	gcc -o shlanga.o -c shlanga.c $(CFLAGS)

main.o: main.c snake.h shlanga.h menu.h bonus.h min-max.h structures.h
	gcc -o main.o -c main.c $(CFLAGS)

menu.o: menu.c menu.h structures.h
	gcc -o menu.o -c menu.c $(CFLAGS)

min-max.o: min-max.c min-max.h structures.h snake.h shlanga.h
	gcc -o min-max.o -c min-max.c $(CFLAGS)

bonus.o: bonus.c bonus.h structures.h
	gcc -o bonus.o -c bonus.c $(CFLAGS)

file.o: file.c file.h structures.h
	gcc -o file.o -c file.c $(CFLAGS)

test_unitaires.o: test_unitaires.c snake.h shlanga.h menu.h bonus.h min-max.h structures.h
	gcc -o test_unitaires.o -c test_unitaires.c $(CFLAGS)

clean:
	rm -rf *.o snake test_unitaires

mrproper: clean
	rm -rf snake test_unitaires