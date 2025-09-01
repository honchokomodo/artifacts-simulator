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
	stats = compute_base_stats(stats);

	accumulator_print(stats);

	return 0;
}

