#ifndef CHARACTER_DEFS_H
#define CHARACTER_DEFS_H

#include "common.h"
#include "../build/include/characters_enum.h"

typedef struct character_stats {
	CharacterType type;
	int level;
	int constellation;
	struct {
		int normal;
		int skill;
		int burst;
	} talent;
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

#endif
