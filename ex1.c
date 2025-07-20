#include "character.c"
#include <time.h>

int main(void)
{
	srand(time(NULL));

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
	newarti = ARTIFACT_NEW(rand() % 5 == 0, .set = ONSET, .piece = FLOWER);
	// upgrade the artifact 5 times up to lv 20
	for (int i = 0; i < 5; i++)
		newarti = artifact_upgrade(newarti);
	// give the arti to skirk
	skirk_with_eshu.artifacts[FLOWER] = newarti;

	// repeat for each other arti slot
	newarti = ARTIFACT_NEW(rand() % 5 == 0, .set = ONSET, .piece = FEATHER);
	for (int i = 0; i < 5; i++)
		newarti = artifact_upgrade(newarti);
	skirk_with_eshu.artifacts[FEATHER] = newarti;

	newarti = ARTIFACT_NEW(rand() % 5 == 0, .set = ONSET, .piece = SANDS, .mainstat.type = ATK_PERCENT);
	for (int i = 0; i < 5; i++)
		newarti = artifact_upgrade(newarti);
	skirk_with_eshu.artifacts[SANDS] = newarti;
	
	newarti = ARTIFACT_NEW(rand() % 5 == 0, .set = ONSET, .piece = GOBLET, .mainstat.type = CRYO_BONUS);
	for (int i = 0; i < 5; i++)
		newarti = artifact_upgrade(newarti);
	skirk_with_eshu.artifacts[GOBLET] = newarti;

	newarti = ARTIFACT_NEW(rand() % 5 == 0, .set = ONSET, .piece = CIRCLET, .mainstat.type = CRIT_DAMAGE);
	for (int i = 0; i < 5; i++)
		newarti = artifact_upgrade(newarti);
	skirk_with_eshu.artifacts[CIRCLET] = newarti;

	character_print(skirk_with_eshu);

	return 0;
}
