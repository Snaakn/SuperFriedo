CC = gcc
SDLFLAGS = -lSDL2main -lSDL2 -lSDL2_image
camera.o: src/camera.c
	gcc -c src/camera.c

level.o: src/level.h
	gcc -c src/level.c

gamewindow.o:
	gcc -c src/gamewindow.c

player.o: src/player.h
	gcc -c src/player.c

unix: src/gamewindow.h src/player.h gamewindow.o player.o level.o camera.o
	gcc -o game gamewindow.o player.o level.o camera.o src/game.c $(SDLFLAGS)
	-rm gamewindow.o player.o level.o camera.o
	./game

win: src/gamewindow.h src/player.h gamewindow.o player.o level.o camera.o
	gcc -o game gamewindow.o player.o level.o camera.o src/game.c -lmingw32 $(SDLFLAGS)
	del *.o
	del *.ghc
	./game.exe
