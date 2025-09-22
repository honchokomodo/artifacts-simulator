#ifndef DAMAGE_UTIL_C
#define DAMAGE_UTIL_C

#include <math.h>

typedef enum reaction_type {
	REACTION_NOTHING,
	FORWARD_MELT,
	REVERSE_MELT,
	FORWARD_VAPORIZE,
	REVERSE_VAPORIZE,
	REACTION_COUNT,
} ReactionType;

typedef struct enemy {
	int level;
	float def_reduce;
	float def_ignore;
	float physical_res;
	float pyro_res;
	float hydro_res;
	float electro_res;
	float cryo_res;
	float dendro_res;
	float anemo_res;
	float geo_res;
} Enemy;

float enemy_defense_fac(Enemy enemy, int character_level)
{
	float enemy_def = 5 * enemy.level + 500;

	float def_reduce = enemy.def_reduce;
	if (def_reduce > 90) def_reduce = 90;
	float def_ignore = enemy.def_ignore;
	enemy_def *= 1 - def_reduce / 100;
	enemy_def *= 1 - def_ignore / 100;

	float enemy_dmg_reduce = enemy_def / (enemy_def + 5 * character_level + 500);

	return 1 - enemy_dmg_reduce;
}

float enemy_resistance_fac(float res)
{
	if (isnan(res) || isinf(res)) return 0;
	res /= 100;
	if (res < 0) res /= 2;
	if (res < 0.75) return 1 - res;
	return 1.0 / (4 * res + 1);
}

float amplifying_multiplier(ReactionType reaction, float em, float bonus)
{
	static float const reaction_mult[REACTION_COUNT] = {
		[FORWARD_MELT] = 2,
		[REVERSE_MELT] = 1.5,
		[FORWARD_VAPORIZE] = 2,
		[REVERSE_VAPORIZE] = 1.5,
	};

	if (reaction == REACTION_NOTHING) return 1;

	float em_bonus = 2.78 * em / (em + 1400);
	return reaction_mult[reaction] * (1 + em_bonus + bonus);
}

#endif
