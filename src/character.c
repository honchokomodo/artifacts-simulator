#ifndef CHARACTER_C
#define CHARACTER_C

#include "common.h"

typedef enum character_type {
	CHARACTER_NOTHING,
#define TEMPLATE_CharacterType
#include "characters/characters_list.h"
#undef TEMPLATE_CharacterType
} CharacterType;

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

typedef enum crit_mode {
	OFF_CRIT,
	ON_CRIT,
	MEAN_CRIT,
} CritMode;

typedef struct character_attack_args {
	CharacterStats character;
	// for aggregating stats without touching character base stats
	StatAccumulators stats;
	// Enemy enemy
	CritMode crit;
	// ReactionType reaction;
} CharacterAttackArgs;

typedef struct character_talent_args {
	CharacterStats character;
	// for aggregating stats without touching character base stats
	StatAccumulators accumulators;
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

	in.stats.ar[HP_BASE] = base_hp * lvlmul + asc_hp * ascmul;
	in.stats.ar[ATK_BASE] = base_atk * lvlmul + asc_atk * ascmul;
	in.stats.ar[DEF_BASE] = base_def * lvlmul + asc_def * ascmul;
	in.stats.ar[CRIT_RATE] = 5.0;
	in.stats.ar[CRIT_DAMAGE] = 50.0;
	in.stats.ar[ENERGY_RECHARGE] = 100.0;

	return in;
}

#define TEMPLATE_character2talent_impl
#include "characters/characters_list.h"
#undef TEMPLATE_character2talent_impl

#define TEMPLATE_character2generator_impl
#include "characters/characters_list.h"
#undef TEMPLATE_character2generator_impl

char const * const character2str[] = {
	[CHARACTER_NOTHING] = "nil character",
#define TEMPLATE_character2str
#include "characters/characters_list.h"
#undef TEMPLATE_character2str
};

char const * const character2icon[] = {
	[CHARACTER_NOTHING] = "resources/images/characters/character_nothing_icon.png",
#define TEMPLATE_character2icon
#include "characters/characters_list.h"
#undef TEMPLATE_character2icon
};

char const * const character2portrait[] = {
	[CHARACTER_NOTHING] = "resources/images/characters/character_nothing_portrait.png",
#define TEMPLATE_character2portrait
#include "characters/characters_list.h"
#undef TEMPLATE_character2portrait
};

CharacterTalentFunc const character2talent[] = {
	[CHARACTER_NOTHING] = noop_talent_func,
#define TEMPLATE_character2talent_arr
#include "characters/characters_list.h"
#undef TEMPLATE_character2talent_arr
};

CharacterGeneratorFunc const character2generator[] = {
	[CHARACTER_NOTHING] = noop_character_generator_func,
#define TEMPLATE_character2generator_arr
#include "characters/characters_list.h"
#undef TEMPLATE_character2generator_arr
};

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
