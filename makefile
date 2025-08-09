ifeq ($(OS), Windows_NT)
	CCFLAGS += -lgdi32 -lwinmm
endif

run: build/main
	build/main

build/main: src/*.c build build/include/character_*.h
	gcc -o build/main src/main.c -Llib -Iinclude -lm -lraylib $(CCFLAGS)

build/include/character_*.h: build/generate_characters build/include
	build/generate_characters

build/generate_characters: src/generate_characters.c
	gcc -o build/generate_characters src/generate_characters.c

build/include:
	mkdir -p build/include

build:
	mkdir -p build
