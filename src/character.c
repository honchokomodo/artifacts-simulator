#ifndef CHARACTER_C
#define CHARACTER_C

//#include "../build/include/characters_enum.h"
//#include "character_defs.h"
//#include "../build/include/characters_impls.h"
#include "../build/include/characters_arrs.h"

// compute all character stats from:
// type, level, ascension, talents, constellation
#define CHARACTER_NEW(type, ...) character_new(type, (CharacterStats) {__VA_ARGS__})
CharacterStats character_new(CharacterType type, CharacterStats in)
{
	return character2generator[type](in);
}

void character_talents(CharacterTalentArgs in)
{
	character2talent[in.character.type](in);
}

#endif
