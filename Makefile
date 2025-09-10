CC=gcc
PWD = $(shell pwd)

all:
	$(CC) -Wall -Wextra -pedantic $(PWD)/main.c `pkg-config --cflags --libs sdl2` -ggdb -lSDL2_ttf -o game


