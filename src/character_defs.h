#ifndef CHARACTER_DEFS_H
#define CHARACTER_DEFS_H

#include "common.h"
#include "../build/include/characters_enum.h"

typedef struct character_stats {
	CharacterType type;
	int level;
	int ascension;
	int constellation;
	struct {
		int normal;
		int skill;
		int burst;
	} talent;
	StatAccumulators stats;
} CharacterStats;

// TODO: figure this out
typedef struct character_talent_args {
	CharacterStats character;
	StatAccumulators * accumulators;
} CharacterTalentArgs;

// TODO: figure this out
typedef void (*CharacterTalentFunc)(CharacterTalentArgs in);
void noop_talent_func(CharacterTalentArgs in)
{
	// this function is supposed to do nothing
}

// TODO: fix this
typedef CharacterStats (*CharacterGeneratorFunc)(CharacterStats in);
CharacterStats noop_character_generator_func(CharacterStats in)
{
	return in; // do nothing
}

// TODO: check if this works
CharacterStats character_base_stats(CharacterStats in, int quality, int level,
		int ascension, float base_hp, float base_atk, float base_def,
		float asc_hp, float asc_atk, float asc_def)
{
	static float const asctbl[] = {
		[0] = 0.0 / 182.0,
		[1] = 38.0 / 182.0,
		[2] = 65.0 / 182.0,
		[3] = 101.0 / 182.0,
		[4] = 128.0 / 182.0,
		[5] = 155.0 / 182.0,
		[6] = 182.0 / 182.0,
	};

	// simplified version of the formula on the wiki
	float lvlmul = ((level * 272477) + 3027523) / 3300000.0 +
		(quality == 5) *
		(-0.000545558586118 + 0.000443691458696 * level +
		0.0000433830491622 * level * level);

	float ascmul = asctbl[ascension];

	in.stats.ar[HP_BASE] = base_hp * lvlmul + asc_hp * ascmul;
	in.stats.ar[ATK_BASE] = base_atk * lvlmul + asc_atk * ascmul;
	in.stats.ar[DEF_BASE] = base_def * lvlmul + asc_def * ascmul;
	in.stats.ar[CRIT_RATE] = 5.0;
	in.stats.ar[CRIT_DAMAGE] = 50.0;
	in.stats.ar[ENERGY_RECHARGE] = 100.0;

	return in;
}

#endif
