CC=gcc
PWD = $(shell pwd)

all:
	$(CC) -Wall $(PWD)/*.c `pkg-config --cflags --libs sdl2` -lm -lSDL2_ttf -o game


