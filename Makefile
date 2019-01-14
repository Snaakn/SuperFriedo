CC = gcc
SDLFLAGS = -lSDL2main -lSDL2 -lSDL2_image

level.o: src/level.h
	gcc -c src/level.c

gamewindow.o:
	gcc -c src/gamewindow.c

player.o: src/player.h
	gcc -c src/player.c

unix: src/gamewindow.h src/player.h gamewindow.o player.o level.o
	gcc -o game gamewindow.o player.o level.o src/game.c $(SDLFLAGS)
	-rm gamewindow.o player.o level.o
	./game

win:	src/gamewindow.h src/player.h src/level.h gamewindow.o level.o
	gcc -o game.exe gamewindow.o player.o level.o src/game.c $(SDLFLAGS) -lmingw32
