#ifndef CHARACTER_C
#define CHARACTER_C

#include "artifact.c"
#include "weapon.h"

typedef enum character_type {
	CHARACTER_NOTHING,
	AMBER,
	SKIRK,
} CharacterType;

typedef struct character_base {
	CharacterType type;
	int level;

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
} CharacterBase;

typedef struct character_build {
	CharacterBase character;
	Weapon weapon;

/*
	// keep section in sync with struct artifact_loadout in artifact.c
	// this union is just for qol so that we can do .piece instead of
	// .loadout.piece every time
	// this may lead to some issues with compiler optimizations
	union {
		ArtifactLoadout loadout;
		struct {
*/
			Artifact flower;
			Artifact feather;
			Artifact sands;
			Artifact goblet;
			Artifact circlet;
/*
		};
	};
*/
} CharacterBuild;

CharacterBase amber90 = {
	.type = AMBER,
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
	.type = SKIRK,
	.level = 90,
	
	// values obtained from wiki
	.hp = 12417.35,
	.atk = 358.77,
	.def = 806.21,
	.crit_rate = 5.0,
	.crit_damage = 50.0 + 38.4,
	.energy_recharge = 100.0,
};

void characterbuild_print(CharacterBuild in)
{
	//TODO: IMPLEMENT THIS
}

#endif
