RAYLIB ?= ./external/raylib/src/

all:
	g++ src/main.cpp src/functions.cpp -o out -Ofast -I $(RAYLIB) -L $(RAYLIB) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./out
