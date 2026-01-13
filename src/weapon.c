#ifndef WEAPON_C
#define WEAPON_C

#include "common.h"

typedef enum weapon_type {
	WEAPON_NOTHING,
#define TEMPLATE_WeaponType
#include "weapons/weapons_list.h"
#undef TEMPLATE_WeaponType
} WeaponType;

typedef struct weapon {
	WeaponType type;
	int level;
	int ascension;
	int refinement;

	float atk;
	Affix bonus;
	int passivedata;
} Weapon;

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

#define TEMPLATE_weapon2generator_impl
#include "weapons/weapons_list.h"
#undef TEMPLATE_weapon2generator_impl

char const * const weapon2str[] = {
	[WEAPON_NOTHING] = "nil weapon",
#define TEMPLATE_weapon2str
#include "weapons/weapons_list.h"
#undef TEMPLATE_weapon2str
};

char const * const weapon2icon[] = {
	[WEAPON_NOTHING] = "resources/images/weapons/weapon_nothing_icon.png",
#define TEMPLATE_weapon2icon
#include "weapons/weapons_list.h"
#undef TEMPLATE_weapon2icon
};

char const * const weapon2icon_asc[] = {
	[WEAPON_NOTHING] = "resources/images/weapons/weapon_nothing_asc_icon.png",
#define TEMPLATE_weapon2icon_asc
#include "weapons/weapons_list.h"
#undef TEMPLATE_weapon2icon_asc
};

WeaponGeneratorFunc const weapon2generator[] = {
	[WEAPON_NOTHING] = noop_weapon_generator_func,
#define TEMPLATE_weapon2generator_arr
#include "weapons/weapons_list.h"
#undef TEMPLATE_weapon2generator_arr
};

// compute all weapon stats from:
// type, level, ascension, refinement
#define WEAPON_NEW(type, ...) weapon_new(type, (Weapon) {__VA_ARGS__})
Weapon weapon_new(WeaponType type, Weapon in)
{
	return weapon2generator[type](in);
}

char const * weapon_icon(Weapon in)
{
	if (in.ascension >= 2)
		return weapon2icon_asc[in.type];
	return weapon2icon[in.type];
}

#endif
