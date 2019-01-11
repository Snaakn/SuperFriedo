CC = gcc
CFLAGS = "-std="c99" -Wall -pedantic src/friedo.c -o friedolin.exe"

unix:
	gcc -std="c99" -Wall -pedantic src/friedo.c -o friedolin -lSDL2main -lSDL2 -lSDL2_image

win:
	$(CC) $(CFLAGS) -lSDL2main -lSDL2 -lmingw32
winkon:
	 $(CC) $(CFLAGS) -L C:\lmingw -lSDL2main -lSDL2 -lmingw32
