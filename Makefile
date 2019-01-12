CC = gcc
CFLAGS = src/friedo.c -o friedolin"
SDLFLAGS = -lSDL2main -lSDL2 -lSDL2_image

gamewindow.o:
	gcc -c src/gamewindow.c

unix: src/gamewindow.h gamewindow.o
	gcc -o game gamewindow.o src/game.c $(SDLFLAGS)
	-rm gamewindow.o
	./game

win:
	gcc -o game.exe gamewindow.o src/game.c $(SDLFLAGS) -lmingw32
