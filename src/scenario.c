#ifndef SCENARIO_C
#define SCENARIO_C

#include "artifact.c"
#include "weapon.c"
#include "character.c"

/*
compendium of nightmare edge cases:

====================CATEGORY: STAT AGGREGATION

Amber, Precise Shot
Description: Aimed Shot hits on weak spots increase ATK by 15% for 10s.
Consequence: Characters contain conditional buffs.

Mavuika, The Ashen Price
Description: If Mavuika is in Nightsoul's Blessing state, increases her base
	ATK by 200, and reduces nearby opponent's DEF by -20% (assumed
	additive).
Consequence: Base HP, ATK, and DEF may be conditionally buffed. Enemies are
	also affected by these.

Gaming, To Tame All Beasts
Description: Increases plunging attack crit rate by 20% and crit damage by 40%.
Consequence: Buffs may buff the stats for specific talents.

Calamity of Eshu, Diffusing Boundary
Description: If the character is shielded, grants Damage Bonus to normal and
	charged attacks, and increases their crit rate.
Consequence: Weapons may contain conditional buffs.

coping mechanisms:
Create configurations for conditional buffs.
Stat aggregation will be per talent/metric.

====================CATEGORY: DAMAGE CALCULATION

Yoimiya, Niwabi Fire-Dance
Description: Infuses Yoimiya's normal attacks and converts their damage to pyro
	damage.
Consequence: A character may have a base damage multiplier. It is multiplied
	onto the base damage before any additive base damage bonus, after which
	extra damage bonuses are applied.

Skirk, Return to Oblivion
Description: Creates up to 3 stacks of "Death's Crossing" which grants varying
	amounts of base damage multiplier. 
Consequence: Buffs may operate in stacks.

Skirk, Havoc: Ruin
Description: Big slash, consumes all of Skirk's "Serpent's Subtlety", with each
	point increasing additive base damage by some factor of her ATK.
Consequence: character buffs may depend on the character's aggregate stats.

Calamity of Eshu, Diffusing Boundary
Description: If the character is shielded, grants Damage Bonus to normal and
	charged attacks, and increases their crit rate.
Consequence: Weapons may contain conditional buffs.

Wanderer's Troupe, 4-piece
Description: Increases Charged Attack DMG by 35% if the character uses a
	Catalyst or Bow.
Consequence: Buffs may depend on character weapon type.

Emblem of Severed Fate, 4-piece
Description: Increases Elemental Burst DMG by 25% of Energy Recharge. A maximum
	of 75% bonus DMG can be obtained this way.
Consequence: Artifact set bonuses may depend on already aggregated stats.

Skyward Harp, Echoing Ballad
Description: ... Hits have a 60% chance to inflict a small AoE attack, dealing
	125% Physical ATK DMG ...
Consequence: Weapons can do damage on their own.

Ocean-Hued Clam, 4-piece
Description: ... the Sea-Dyed Foam will explode, dealing DMG to nearby
	opponents based on 90% of the accumulated healing.
Consequence: Artifact sets can do damage.

Viridescent Venerer, 4-piece
Description: Increases Swirl DMG by 60%. Decreases opponent's Elemental RES to
	the element infused in the swirl by 40% for 10s.
Consequence: Damage may be buffed per reaction. Artifact sets may affect enemy
	resistances.

coping mechanisms:
Damage calculation will be handled after all stats are completely aggregated.
Damage bonuses will be included in stat aggregation.

====================CATEGORY: EXTERNAL EFFECTS

Mavuika, The Ashen Price
Description: If Mavuika is in Nightsoul's Blessing state, increases her base
	ATK by 200, and reduces nearby opponent's DEF by -20% (assumed
	additive).
Consequence: Base HP, ATK, and DEF may be conditionally buffed. Enemies are
	also affected by these.

Viridescent Venerer, 4-piece
Description: Increases Swirl DMG by 60%. Decreases opponent's Elemental RES to
	the element infused in the swirl by 40% for 10s.
Consequence: Damage may be buffed per reaction. Artifact sets may affect enemy
	resistances.

*/

StatAccumulators acc_character_stats(StatAccumulators in,
		CharacterStats character)
{
	return accumulator_combine(in, character.stats);
}

StatAccumulators acc_weapon_stats(StatAccumulators in, Weapon weapon)
{
	in.ar[ATK_BASE] += weapon.atk;
	in.ar[weapon.bonus.type] += weapon.bonus.value;

	return in;
}

StatAccumulators acc_artifact_stats(StatAccumulators in, Artifact artifact)
{
	in.ar[artifact.mainstat.type] += artifact.mainstat.value;
	for (int i = 0; i < artifact.num_substats; i++) {
		Affix substat = artifact.substat[i];
		in.ar[substat.type] += substat.value;
	}

	return in;
}

StatAccumulators compute_base_stats(StatAccumulators in)
{
	float hp_fac = 1 + in.ar[HP_PERCENT] / 100;
	float atk_fac = 1 + in.ar[ATK_PERCENT] / 100;
	float def_fac = 1 + in.ar[DEF_PERCENT] / 100;

	in.ar[HP_AGGREGATE] = in.ar[HP_BASE] * hp_fac + in.ar[HP_FLAT];
	in.ar[ATK_AGGREGATE] = in.ar[ATK_BASE] * atk_fac + in.ar[ATK_FLAT];
	in.ar[DEF_AGGREGATE] = in.ar[DEF_BASE] * def_fac + in.ar[DEF_FLAT];

	return in;
}

#endif
