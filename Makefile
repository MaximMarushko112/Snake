all: game.exe

game.exe: game.o snake.o
	gcc game.o snake.o -o game.exe -lncurses

game.o: game.c
	gcc -c game.c 

snake.o: snake.c snake.h
	gcc -c snake.c -lncurses