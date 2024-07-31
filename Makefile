all: game

game: main.o snake.o
	gcc snake.o main.o -o game -lncurses

main.o: main.c
	gcc -c main.c 

snake.o: snake.c snake.h
	gcc -c snake.c -lncurses