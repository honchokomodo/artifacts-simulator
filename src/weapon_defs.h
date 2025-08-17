#ifndef WEAPON_DEFS_H
#define WEAPON_DEFS_H

#include "common.h"
#include "../build/include/weapons_enum.h"

typedef struct weapon {
	WeaponType type;
	int level;
	int ascension;
	int refinement;

	float atk;
	Affix bonus;
	int passivedata;
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

float weapon_base_atk(int level, int ascension, int const table[14])
{
	static int const tarr[] = {
		[0] = 0,
		[1] = 20,
		[2] = 40,
		[3] = 50,
		[4] = 60,
		[5] = 70,
		[6] = 80,
		[7] = 90,
	};

	int tmin = tarr[ascension];
	int tmax = tarr[ascension + 1];
	float trange = tmax - tmin;
	float t = (level - tmin) / trange;

	int a = table[2 * ascension];
	int b = table[2 * ascension + 1];

	float out = a + t * (b - a);

	return out;
}

float weapon_bonus_factor(int level)
{
	level /= 5;
	if (level == 0) return 1;
	level *= 5;
	return 0.040383 * level + 0.959588;
}

#endif
