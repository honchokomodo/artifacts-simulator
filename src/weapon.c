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

void weapon_passive(WeaponPassiveArgs in)
{
	weapon2passive[in.weapon.type](in);
}

char const * weapon_icon(Weapon in)
{
	if (in.ascension >= 2)
		return weapon2icon_asc[in.type];
	return weapon2icon[in.type];
}

#endif
