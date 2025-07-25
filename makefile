run: build/main
	build/main

build/main: src/*.c build
	gcc -o build/main src/main.c -Iinclude -lm -lraylib

build:
	mkdir -p build
