#include <stdlib.h>
#include <time.h>

#include "../character.c"

int main(void)
{
	srand(time(NULL));

	CharacterBuild skirk = {
		.character = CHARACTER_NEW(SKIRK, .level = 90),
		.weapon = calamity_of_eshu_r5_90,
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
/*
		.flower = ARTIFACT_NEW(rand() % 5 == 0,
				.level = 20,
				.set = FINALE_OF_THE_DEEP_GALLERIES,
				.piece = FLOWER),
		.feather = ARTIFACT_NEW(rand() % 5 == 0,
				.level = 20,
				.set = FINALE_OF_THE_DEEP_GALLERIES,
				.piece = FEATHER),
		.sands = ARTIFACT_NEW(rand() % 5 == 0,
				.level = 20,
				.set = FINALE_OF_THE_DEEP_GALLERIES,
				.piece = SANDS,
				.mainstat.type = ATK_PERCENT),
		.goblet = ARTIFACT_NEW(rand() % 5 == 0,
				.level = 20,
				.set = FINALE_OF_THE_DEEP_GALLERIES,
				.piece = GOBLET,
				.mainstat.type = CRYO_BONUS),
		.circlet = ARTIFACT_NEW(rand() % 5 == 0,
				.level = 20,
				.set = FINALE_OF_THE_DEEP_GALLERIES,
				.piece = CIRCLET,
				.mainstat.type = CRIT_DAMAGE),
*/
	};

	characterbuild_print(skirk);

	return 0;
}

