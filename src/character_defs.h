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
	int normaldata;
	int skilldata;
	int burstdata;
	int a1data;
	int a4data;
	int utildata;
	int c1data;
	int c2data;
	int c3data;
	int c4data;
	int c5data;
	int c6data;

	char * name;

	float hp;
	float hp_percent;
	float atk;
	float atk_percent;
	float def;
	float def_percent;
	float elemental_mastery;
	// max stamina
	
	float crit_rate;
	float crit_damage;
	float healing_bonus;
	// incoming healing bonus
	float energy_recharge;
	// cd reduction
	// shield strength
	
	float pyro_bonus;
	// pyro res
	float hydro_bonus;
	// hydro res
	float dendro_bonus;
	// dendro res
	float electro_bonus;
	// electro res
	float anemo_bonus;
	// anemo res
	float cryo_bonus;
	// cryo res
	float geo_bonus;
	// geo res
	float physical_bonus;
	// physical res
} CharacterStats;

typedef struct character_talent_args {
	CharacterStats character;
	float * accumulators;
	float * hp_base;
	float * atk_base;
	float * def_base;
	float * factor;
} CharacterTalentArgs;

typedef void (*CharacterTalentFunc)(CharacterTalentArgs in);
void noop_talent_func(CharacterTalentArgs in)
{
	// this function is supposed to do nothing
}

typedef CharacterStats (*CharacterGeneratorFunc)(CharacterStats in);
CharacterStats noop_character_generator_func(CharacterStats in)
{
	return in; // do nothing
}

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

	in.hp = base_hp * lvlmul + asc_hp * ascmul;
	in.atk = base_atk * lvlmul + asc_atk * ascmul;
	in.def = base_def * lvlmul + asc_def * ascmul;
	in.crit_rate = 5.0;
	in.crit_damage = 50.0;
	in.energy_recharge = 100.0;

	return in;
}

int character_check_ascension(int level, int ascension)
{
	int min = 0;
	if (level <= 20) min = 0;
	else if (level <= 40) min = 1;
	else min = (level - 1) / 10 - 2;

	int max = 0;
	if (level < 20) max = 0;
	else if (level < 40) max = 1;
	else max = level / 10 - 2;

	if (ascension <= min) return min;
	if (ascension >= max) return max;
	return ascension;
}

#endif
