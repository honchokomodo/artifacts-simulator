#include <stdlib.h>
#include <time.h>

#include "../scenario.c"

int main(void)
{
	srand(time(NULL));

	CharacterStats skirk = CHARACTER_NEW(SKIRK, .level = 90, .talent = {6, 8, 7});
	Weapon calamity_of_eshu = WEAPON_NEW(CALAMITY_OF_ESHU, .level = 90, .refinement = 5);
	ArtifactLoadout loadout = {
		.flower = {
			.piece = FLOWER, 
			.set = FINALE_OF_THE_DEEP_GALLERIES,
			.level = 20, .num_substats = 4,
			.mainstat = {HP_FLAT, 4780},
			.substat[0] = {CRIT_RATE, 7.8},
			.substat[1] = {ELEMENTAL_MASTERY, 42},
			.substat[2] = {ATK_PERCENT, 8.2},
			.substat[3] = {DEF_FLAT, 39},
		},

		.feather = {
			.piece = FEATHER,
			.set = FINALE_OF_THE_DEEP_GALLERIES,
			.level = 20, .num_substats = 4,
			.mainstat = {ATK_FLAT, 311},
			.substat[0] = {CRIT_RATE, 7.0},
			.substat[1] = {DEF_PERCENT, 5.8},
			.substat[2] = {CRIT_DAMAGE, 18.7},
			.substat[3] = {HP_FLAT, 598},
		},

		.sands = {
			.piece = SANDS,
			.set = WANDERERS_TROUPE,
			.level = 20, .num_substats = 4,
			.mainstat = {ATK_PERCENT, 46.6},
			.substat[0] = {CRIT_DAMAGE, 20.2},
			.substat[1] = {HP_PERCENT, 19.2},
			.substat[2] = {ELEMENTAL_MASTERY, 23},
			.substat[3] = {DEF_PERCENT, 5.1},
		},

		.goblet = {
			.piece = GOBLET,
			.set = FINALE_OF_THE_DEEP_GALLERIES,
			.level = 20, .num_substats = 4,
			.mainstat = {CRYO_BONUS, 46.6},
			.substat[0] = {ELEMENTAL_MASTERY, 33},
			.substat[1] = {HP_PERCENT, 9.3},
			.substat[2] = {ENERGY_RECHARGE, 18.1},
			.substat[3] = {ATK_FLAT, 19},
		},

		.circlet = {
			.piece = CIRCLET,
			.set = FINALE_OF_THE_DEEP_GALLERIES,
			.level = 20, .num_substats = 4,
			.mainstat = {CRIT_DAMAGE, 62.2},
			.substat[0] = {CRIT_RATE, 9.7},
			.substat[1] = {HP_PERCENT, 9.3},
			.substat[2] = {ATK_PERCENT, 5.3},
			.substat[3] = {HP_FLAT, 478},
		},
	};

	StatAccumulators stats = {0};

	stats = acc_character_stats(stats, skirk);
	stats = acc_weapon_stats(stats, calamity_of_eshu);
	stats = acc_artifact_stats(stats, loadout.flower);
	stats = acc_artifact_stats(stats, loadout.feather);
	stats = acc_artifact_stats(stats, loadout.sands);
	stats = acc_artifact_stats(stats, loadout.goblet);
	stats = acc_artifact_stats(stats, loadout.circlet);
	stats = compute_base_stats(stats);

	accumulator_print(stats);

	return 0;
}

