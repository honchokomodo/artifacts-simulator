#ifndef CHARACTER_UI_C
#define CHARACTER_UI_C

#include "character.c"
#include "components.c"

typedef struct character_ui_args {
	CharacterStats character;
	size_t * len;
	BuffElement * arr;
	bool * sentinel;
} CharacterUIArgs;

typedef void (*CharacterUIFunc)(CharacterUIArgs args);
void noop_character_ui_func(CharacterUIArgs args) {
	// this function does nothing
}

#define TEMPLATE_character2ui_impl
#include "characters/characters_list.h"
#undef TEMPLATE_character2ui_impl

CharacterUIFunc const character2ui[] = {
	[CHARACTER_NOTHING] = noop_character_ui_func,
#define TEMPLATE_character2ui_arr
#include "characters/characters_list.h"
#undef TEMPLATE_character2ui_arr
};

#endif
