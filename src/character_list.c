#ifndef CHARACTER_LIST_C
#define CHARACTER_LIST_C

#include "character.c"

CharacterBase amber90 = {
	.name = "Amber",
	.level = 90,

	// values obtained from wiki
	.hp = 9461.18,
	.atk = 223.02,
	.atk_percent = 24.0,
	.def = 600.62,
	.crit_rate = 5.0,
	.crit_damage = 50.0,
	.energy_recharge = 100.0,
};

CharacterBase skirk90 = {
	.name = "Skirk",
	.level = 90,
	
	// values obtained from wiki
	.hp = 12417.35,
	.atk = 358.77,
	.def = 806.21,
	.crit_rate = 5.0,
	.crit_damage = 50.0 + 38.4,
	.energy_recharge = 100.0,
};

#endif
