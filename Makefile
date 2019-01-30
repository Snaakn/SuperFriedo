CC = gcc
SDLFLAGS = -lSDL2main -lSDL2 -lSDL2_image #-lSDL_ttf

enemy.o: src/enemy.c
	gcc -c src/enemy.c

camera.o: src/camera.c
	gcc -c src/camera.c

level.o: src/level.h
	gcc -c src/level.c

gamewindow.o:
	gcc -c src/gamewindow.c

player.o: src/player.h
	gcc -c src/player.c

unix: src/gamewindow.h src/player.h gamewindow.o player.o level.o camera.o enemy.o
	gcc -o game gamewindow.o player.o level.o camera.o enemy.o src/game.c $(SDLFLAGS)
	-rm *.o
	./game

win: src/gamewindow.h src/player.h gamewindow.o player.o level.o camera.o enemy.o
	gcc -o game gamewindow.o player.o level.o camera.o enemy.o src/game.c -lmingw32 $(SDLFLAGS)
	del *.o
	del *.ghc
	./game.exe
