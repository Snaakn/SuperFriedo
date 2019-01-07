linux:
	gcc -std="c99" -Wall -pedantic friedo.c -o friedolin -lm -lSDL2main -lSDL2

win:
	gcc -std="c99" -Wall -pedantic friedo.c -o friedolin.exe -lm -lSDL2main -lSDL2 -lmingw32
