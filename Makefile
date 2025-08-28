CC=gcc
PWD = $(shell pwd)

all:
	$(CC) -Wall $(PWD)/*.c `pkg-config --cflags --libs sdl2` -lSDL2_ttf -o game


