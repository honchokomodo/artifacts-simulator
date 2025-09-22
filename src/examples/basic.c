#include <stdlib.h>
#include <time.h>

#include "../scenario.c"

int main(void)
{
	srand(time(NULL));

	CharacterStats amber = CHARACTER_NEW(AMBER,
			.level = 90,
			.constellation = 6,
			.talent = {10, 13, 13});

	Weapon skyward_harp = WEAPON_NEW(SKYWARD_HARP,
			.level = 90,
			.refinement = 1);

	ArtifactLoadout loadout = {
		.flower = {
			.piece = FLOWER, 
			.set = WANDERERS_TROUPE,
			.level = 20, .num_substats = 4,
			.mainstat = {HP_FLAT, 4780},
			.substat[0] = {CRIT_RATE, 12.8},
			.substat[1] = {ATK_PERCENT, 9.3},
			.substat[2] = {CRIT_DAMAGE, 7.8},
			.substat[3] = {DEF_PERCENT, 12.4},
		},

		.feather = {
			.piece = FEATHER,
			.set = WANDERERS_TROUPE,
			.level = 20, .num_substats = 4,
			.mainstat = {ATK_FLAT, 311},
			.substat[0] = {CRIT_RATE, 10.9},
			.substat[1] = {ELEMENTAL_MASTERY, 35},
			.substat[2] = {CRIT_DAMAGE, 17.1},
			.substat[3] = {HP_PERCENT, 5.8},
		},

		.sands = {
			.piece = SANDS,
			.set = WANDERERS_TROUPE,
			.level = 20, .num_substats = 4,
			.mainstat = {ELEMENTAL_MASTERY, 187},
			.substat[0] = {CRIT_RATE, 5.4},
			.substat[1] = {ATK_PERCENT, 9.9},
			.substat[2] = {CRIT_DAMAGE, 19.4},
			.substat[3] = {DEF_FLAT, 16},
		},

		.goblet = {
			.piece = GOBLET,
			.level = 20, .num_substats = 4,
			.mainstat = {PYRO_BONUS, 46.6},
			.substat[0] = {CRIT_RATE, 5.4},
			.substat[1] = {ELEMENTAL_MASTERY, 37},
			.substat[2] = {CRIT_DAMAGE, 21.0},
			.substat[3] = {HP_PERCENT, 10.5},
		},

		.circlet = {
			.piece = CIRCLET,
			.set = WANDERERS_TROUPE,
			.level = 20, .num_substats = 4,
			.mainstat = {CRIT_DAMAGE, 62.2},
			.substat[0] = {CRIT_RATE, 10.5},
			.substat[1] = {HP_PERCENT, 15.2},
			.substat[2] = {ELEMENTAL_MASTERY, 16},
			.substat[3] = {HP_FLAT, 239},
		},
	};

	StatAccumulators stats = {0};

	stats = acc_character_stats(stats, amber);
	stats = acc_weapon_stats(stats, skyward_harp);
	stats = acc_artifact_stats(stats, loadout.flower);
	stats = acc_artifact_stats(stats, loadout.feather);
	stats = acc_artifact_stats(stats, loadout.sands);
	stats = acc_artifact_stats(stats, loadout.goblet);
	stats = acc_artifact_stats(stats, loadout.circlet);

	// handle teamwide buffs
	// none atm

	// at this point, stats == aggregate base stats

	// handle unique stat bonuses (artifact set bonuses, etc...)

	// the 2pc bonus unconditionally grants 80 ELEMENTAL_MASTERY
	// the 4pc bonus grants 35 BONUS_DAMAGE if and only if the attack is a
	// charged attack and the wielder is a bow or catalyst.

	// we KNOW that the wanderer's troupe 2pc bonus is active because the
	// artifact loadout was manually set to be that way
	// in the actual implementation, we have to somehow determine that the
	// function for wanderer's troupe should be called, and the number of
	// pieces that are in the loadout.
	stats.ar[ELEMENTAL_MASTERY] += 80;

	// the weapon passive unconditionally grants 20 CRIT_DAMAGE
	// the weapon passive may also deal damage (but we're not dealing with
	// that in this case)
	// in the actual implementation, we have to call the function that
	// cooresponds to the weapon passive
	stats.ar[CRIT_DAMAGE] += 20;

	// at this point, stats == idle stats
	// the stats pretty much match enka.network += entered data inaccuracy
	accumulator_print(compute_base_stats(stats));

	// handle talent-specific bonuses

	// we KNOW that the wanderer's troupe 4pc bonus is active bc the
	// artifact loadout was manually set to be that way, and I've made the
	// decision that I want to calculate for a fully charged shot.
	// in the actual implementation, we have to somehow determine that the
	// function for wanderer's troupe should be called, the number of
	// pieces that are in the loadout, and if the talent matches.
	stats.ar[BONUS_DAMAGE] += 35;

	// at this point, stats == augmented stats
	stats = compute_base_stats(stats);
	// at this point, stats == final stats
	
	// damage calculation
	// calculating damage against a lv 103 cryo regisvine:
	// REACTION_NOTHING: 2815
	// REACTION_NOTHING crit: 8375
	// REVERSE_VAPORIZE: 6598
	// REVERSE_VAPORIZE crit: 19627
	// FORWARD_MELT: 8797
	// FORWARD_MELT crit: 26172
	CharacterAttackArgs args = {
		.character = amber,
		.stats = stats,
		.enemy = {
			.level = 103,
			.pyro_res = 10,
		},
		.crit = ON_CRIT,
		.reaction = FORWARD_MELT,
	};

	float damage = amber_fully_charged_shot(args);

	printf("damage: %f\n", damage);

	return 0;
}

