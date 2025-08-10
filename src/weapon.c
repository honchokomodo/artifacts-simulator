#ifndef WEAPON_C
#define WEAPON_C

#include "../build/include/weapons_arrs.h"

// compute all weapon stats from:
// type, level, ascension, refinement
#define WEAPON_NEW(type, ...) weapon_new(type, (Weapon) {__VA_ARGS__})
Weapon weapon_new(WeaponType type, Weapon in)
{
	return weapon2generator[type](in);
}

#endif
