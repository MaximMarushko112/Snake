all: game

game: main.o snake_graphics.o snake_input.o snake_logic.o
	gcc snake.o main.o -o game -lncurses

main.o: main.c
	gcc -c main.c 

snake_graphics.o: snake_graphics.c snake_graphics.h snake_logic.h
	gcc -c snake_graphics.c -lncurses

snake_input.o: snake_input.c snake_input.h snake_logic.h
	gcc -c snake_input.c -lncurses

snake_logic.o: snake_logic.c snake_logic.h snake_graphics.h
	gcc -c snake_logic.c -lncurses