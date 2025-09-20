#ifndef ENEMY_C
#define ENEMY_C

#include <math.h>

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

#endif
