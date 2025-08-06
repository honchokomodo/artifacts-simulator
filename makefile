ifeq ($(OS), Windows_NT)
	CCFLAGS += -lgdi32 -lwinmm
endif

run: build/main
	build/main

build/main: src/*.c build/include/characters_enum.h
	gcc -o build/main src/main.c -Llib -Iinclude -lm -lraylib $(CCFLAGS)

build/include/characters_enum.h: build/include
	gcc -o build/generate_characters src/generate_characters.c
	build/generate_characters

build/include:
	mkdir -p build/include

build:
	mkdir -p build
