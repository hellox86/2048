CC=gcc
PWD = $(shell pwd)

all:
	$(CC) -Wall $(PWD)/main.c `pkg-config --cflags --libs sdl2` -ggdb -lSDL2_ttf -lm -pthread -o game


