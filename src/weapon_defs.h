#ifndef WEAPON_DEFS_H
#define WEAPON_DEFS_H

#include "common.h"
#include "../build/include/weapons_enum.h"

typedef struct weapon {
	WeaponType type;
	int level;
	int ascension;
	int refinement;

	char * name;
	float atk;
	Affix bonus;
	int passivedata;
	//WeaponBonusHandlerFunc passive; //TODO: remove this
} Weapon;

typedef struct weapon_passive_args {
	Weapon weapon;
	StatAccumulators * accumulators;
} WeaponPassiveArgs;

typedef void (*WeaponPassiveFunc)(WeaponPassiveArgs in);
void noop_passive_func(WeaponPassiveArgs in)
{
	// this function is supposed to do nothing
}

typedef Weapon (*WeaponGeneratorFunc)(Weapon in);
Weapon noop_weapon_generator_func(Weapon in)
{
	return in; // do nothing
}

#endif
