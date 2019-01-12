CC = gcc
SDLFLAGS = -lSDL2main -lSDL2 -lSDL2_image

gamewindow.o:
	gcc -c src/gamewindow.c

player.o: src/player.h
	gcc -c src/player.c

unix: src/gamewindow.h src/player.h gamewindow.o player.o
	gcc -o game gamewindow.o player.o src/game.c $(SDLFLAGS)
	-rm gamewindow.o player.o
	./game

win:	src/gamewindow.h src/player.h gamewindow.o
	gcc -o game.exe gamewindow.o player.o src/game.c $(SDLFLAGS) -lmingw32
