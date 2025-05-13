FILES := $(wildcard src/*.c)

all:
	gcc -g -Wall main.c $(FILES) -o main -I. -L./lib -lglew32 -lopengl32 -lglfw3dll