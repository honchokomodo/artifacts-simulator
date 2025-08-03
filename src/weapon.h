#ifndef WEAPON_H
#define WEAPON_H

#include "common.h"

typedef enum weapon_type {
	WEAPON_NOTHING,
	SKYWARD_HARP,
	CALAMITY_OF_ESHU,
} WeaponType;

typedef struct weapon {
	WeaponType type;
	int refinement;
	float atk;
	Affix stat;
} Weapon;

Weapon skyward_harp_r1_90 = {
/*
Echoing Ballad
Increases CRIT DMG by 20%. Hits have a 60% chance to inflict a small AoE
attack, dealing 125% Physical ATK DMG. Can only occur once every 4s.
*/
	.type = SKYWARD_HARP,
	.refinement = 1,
	.atk = 674,
	.stat = {CRIT_RATE, 22.1},
};

Weapon calamity_of_eshu_r5_90 = {
/*
Diffusing Boundary
While characters are protected by a Shield, DMG dealt by Normal and Charged
Attacks is increased by 40%, and Normal and Charged Attack CRIT Rate is
increased by 16%.
*/
	.type = CALAMITY_OF_ESHU,
	.refinement = 5,
	.atk = 565,
	.stat = {ATK_PERCENT, 27.6},
};

#endif
