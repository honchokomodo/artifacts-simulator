#ifndef WEAPON_DEFS_H
#define WEAPON_DEFS_H

#include "common.h"

//TODO: autogenerate this
typedef enum weapon_type {
	WEAPON_NOTHING,
	CALAMITY_OF_ESHU,
	SKYWARD_HARP,
	THUNDERING_PULSE,
	MISTSPLITTER_REFORGED,
} WeaponType;

// TODO: autogenerate this
typedef void (*WeaponBonusHandlerFunc)(
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor);

void noop_weapon_bonus_func(
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor)
{
	// this function does nothing
}

typedef struct weapon {
	WeaponType weapon;
	int level;
	int ascension;
	int refinement;

	char * name;
	float atk;
	Affix bonus;
	int passivedata;
	WeaponBonusHandlerFunc passive; //TODO: remove this
} Weapon;

#endif
