ifeq ($(OS), Windows_NT)
	CCFLAGS += -lgdi32 -lwinmm
endif

run: build/main
	build/main

build/main: src/*.c build build/include/character_*.h
	gcc -o build/main src/main.c -Llib -Iinclude -lm -lraylib $(CCFLAGS)

build/include/characters_*.h: build/generate_characters build/include
	build/generate_characters

build/include/weapons_*.h: build/generate_weapons build/include
	build/generate_weapons

build/generate_characters: src/generate_characters.c
	gcc -o build/generate_characters src/generate_characters.c

build/generate_weapons: src/generate_weapons.c
	gcc -o build/generate_weapons src/generate_weapons.c

build/include:
	mkdir -p build/include

build:
	mkdir -p build
