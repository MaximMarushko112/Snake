ifeq ($(origin CC), default)
	CC = gcc
endif

CFLAGS ?= -O2
COMMONINC = -I./include
SRC = ./source

override CFLAGS += $(COMMONINC)

CSRC = main.c source/simple_list.c source/snake_graphics.c source/snake_input.c source/snake_logic.c
COBJ = main.o simple_list.o snake_graphics.o snake_input.o snake_logic.o 

%.o: source/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: all
all: game

game: $(COBJ)
	$(CC) $^ -o $@ $(LDFLAGS) -lncurses

.PHONY: clean
clean:
	rm -rf *.x
	rm -rf *.o
	rm -rf *.log