#ifndef WEAPON_H
#define WEAPON_H

#include "common.h"

/*
typedef enum weapon_type {
	WEAPON_NOTHING,
	CALAMITY_OF_ESHU,
	SKYWARD_HARP,
	MISTSPLITTER_REFORGED,
} WeaponType;
*/

typedef void (*WeaponBonusHandlerFunc)(
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor);

void noop_weapon_bonus_func(
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor)
{
	// this function does nothing
}

typedef struct weapon {
	char * name;
	int refinement;
	float atk;
	Affix stat;
	WeaponBonusHandlerFunc passive;
} Weapon;

/* from wiki:
Diffusing Boundary
While characters are protected by a Shield, DMG dealt by Normal and Charged
Attacks is increased by 40%, and Normal and Charged Attack CRIT Rate is
increased by 16%.
*/
void calamity_of_eshu_r5_passive_func(
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor)
{
	*multiplicative_factor *= 1.4;
	accumulators[CRIT_RATE] += 16.0;
}

Weapon calamity_of_eshu_r5_90 = {
	.name = "Calamity of Eshu",
	.refinement = 5,
	.atk = 565,
	.stat = {ATK_PERCENT, 27.6},
	.passive = calamity_of_eshu_r5_passive_func,
};

Weapon mistsplitter_reforged_r1 = {
/* from wiki:
Mistsplitter's Edge
Gain a 12~24% Elemental DMG Bonus for all elements and receive the might of 
the Mistsplitter's Emblem. At stack levels 1/2/3, Mistsplitter's Emblem provides
a 8/16/28~16/32/56% Elemental DMG Bonus for the character's Elemental Type. 
The character will obtain 1 stack of Mistsplitter's Emblem in each of the 
following scenarios: Normal Attack deals Elemental DMG (stack lasts 5s), casting
Elemental Burst (stack lasts 10s); Energy is less than 100% (stack disappears
when Energy is full). Each stack's duration is calculated independently.
*/
	.name = "Mistsplitter Reforged",
	.refinement = 1,
	.atk = 674,
	.stat = {CRIT_DAMAGE, 44.1},
	.passive = noop_weapon_bonus_func, //TODO: implement this
};

Weapon skyward_harp_r1_90 = {
/* from wiki:
Echoing Ballad
Increases CRIT DMG by 20%. Hits have a 60% chance to inflict a small AoE
attack, dealing 125% Physical ATK DMG. Can only occur once every 4s.
*/
	.name = "Skyward Harp",
	.refinement = 1,
	.atk = 674,
	.stat = {CRIT_RATE, 22.1},
	.passive = noop_weapon_bonus_func, //TODO: implement this
};

#endif
