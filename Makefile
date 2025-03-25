RAYLIB ?= ./external/raylib-5.5/src/

all:
	g++ src/main.cpp -o out -g -I $(RAYLIB) -L $(RAYLIB) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./out
