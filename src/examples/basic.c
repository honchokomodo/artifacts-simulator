#include <stdlib.h>
#include <time.h>

#include "../character.c"

int main(void)
{
	srand(time(NULL));

	CharacterBuild skirk = {
		.character = skirk90,
		.weapon = calamity_of_eshu_r5_90,
		.flower = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = FINALE_OF_THE_DEEP_GALLERIES, .piece = FLOWER),
		.feather = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = FINALE_OF_THE_DEEP_GALLERIES, .piece = FEATHER),
		.sands = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = FINALE_OF_THE_DEEP_GALLERIES, .piece = SANDS, .mainstat.type = ATK_PERCENT),
		.goblet = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = FINALE_OF_THE_DEEP_GALLERIES, .piece = GOBLET, .mainstat.type = CRYO_BONUS),
		.circlet = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = FINALE_OF_THE_DEEP_GALLERIES, .piece = CIRCLET, .mainstat.type = CRIT_DAMAGE),
	};

	characterbuild_print(skirk);

	/*
	Character skirk_with_eshu = {
		.name = "Skirk with Calamity of Eshu",
		.hp = 12417,
		.atk = 924,
		.atk_percent = 27.6,
		.def = 806,
		.crit_rate = 5.0,
		.crit_damage = 88.4,
		.energy_recharge = 100.0,
	};

	Artifact newarti;

	// if rand() % 5 rolls 0, then the arti will have 4 substats
	// same chance as in domains
	newarti = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = ONSET, .piece = FLOWER);
	// give the arti to skirk
	skirk_with_eshu.artifacts[FLOWER] = newarti;

	// repeat for each other arti slot
	newarti = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = ONSET, .piece = FEATHER);
	skirk_with_eshu.artifacts[FEATHER] = newarti;

	newarti = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = ONSET, .piece = SANDS, .mainstat.type = ATK_PERCENT);
	skirk_with_eshu.artifacts[SANDS] = newarti;
	
	newarti = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = ONSET, .piece = GOBLET, .mainstat.type = CRYO_BONUS);
	skirk_with_eshu.artifacts[GOBLET] = newarti;

	newarti = ARTIFACT_NEW(rand() % 5 == 0, .level = 20, .set = ONSET, .piece = CIRCLET, .mainstat.type = CRIT_DAMAGE);
	skirk_with_eshu.artifacts[CIRCLET] = newarti;
	*/

	/*
	skirk_with_eshu.artifacts[FLOWER] = (Artifact) {
		.level = 4, .set = ONSET, .piece = FLOWER,
		.num_substats = 4,
		.mainstat = {HP_FLAT, 1530},
		.substat[0] = {CRIT_RATE, 3.9},
		.substat[1] = {ELEMENTAL_MASTERY, 23},
		.substat[2] = {ATK_PERCENT, 4.1},
		.substat[3] = {DEF_FLAT, 21},
	};

	skirk_with_eshu.artifacts[FEATHER] = (Artifact) {
		.level = 4, .set = ONSET, .piece = FEATHER,
		.num_substats = 4,
		.mainstat = {ATK_FLAT, 100},
		.substat[0] = {CRIT_RATE, 3.9},
		.substat[1] = {HP_FLAT, 239},
		.substat[2] = {HP_PERCENT, 4.7},
		.substat[3] = {DEF_FLAT, 16},
	};

	skirk_with_eshu.artifacts[SANDS] = (Artifact) {
		.level = 20, .set = OFFSET, .piece = SANDS,
		.num_substats = 4,
		.mainstat = {ATK_PERCENT, 46.6},
		.substat[0] = {CRIT_DAMAGE, 20.2},
		.substat[1] = {HP_PERCENT, 19.2},
		.substat[2] = {ELEMENTAL_MASTERY, 23},
		.substat[3] = {DEF_PERCENT, 5.1},
	};

	skirk_with_eshu.artifacts[GOBLET] = (Artifact) {
		.level = 4, .set = ONSET, .piece = GOBLET,
		.num_substats = 4,
		.mainstat = {CRYO_BONUS, 14.9},
		.substat[0] = {ELEMENTAL_MASTERY, 16},
		.substat[1] = {HP_PERCENT, 4.1},
		.substat[2] = {ENERGY_RECHARGE, 5.2},
		.substat[3] = {ATK_FLAT, 19},
	};

	skirk_with_eshu.artifacts[CIRCLET] = (Artifact) {
		.level = 4, .set = ONSET, .piece = CIRCLET,
		.num_substats = 4,
		.mainstat = {CRIT_RATE, 9.9},
		.substat[0] = {ELEMENTAL_MASTERY, 21},
		.substat[1] = {ATK_FLAT, 18},
		.substat[2] = {HP_PERCENT, 4.1},
		.substat[3] = {DEF_FLAT, 23},
	};
	*/

//	character_print(skirk_with_eshu);

	return 0;
}
