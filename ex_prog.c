#include <stdlib.h>
#include <time.h>

#include "character.c"

float rating(Character in)
{
	int numOnset = 0;
	for (int i = FLOWER; i <= CIRCLET; i++)
		if (in.artifacts[i].set == ONSET)
			numOnset += 1;

	if (numOnset >= 2)
		in.crit_rate += 15;

	AggregateStats aggregate = character_aggregate_stats(in);
	float score = aggregate.atk * aggregate.crit * aggregate.cryo_bonus;

	if (numOnset >= 4)
		score *= 1.6;

	return score;
}

int main(void)
{
	srand(time(NULL));

	Character skirk_with_eshu = {
		.name = "Skirk with Calamity of Eshu",
		.hp = 12417,
		.atk = 924,
		.atk_percent = 27.6,
		.def = 806,
		.crit_rate = 5.0 + 16,
		.crit_damage = 88.4,
		.energy_recharge = 100.0,
	};

	for (int i = 0; i < 9 * 7 * 20; i++) {
		Character newbuild = skirk_with_eshu;

		Artifact newarti = artifact_new_domain();
		newarti = artifact_upgrade(newarti);
		newarti = artifact_upgrade(newarti);
		newarti = artifact_upgrade(newarti);
		newarti = artifact_upgrade(newarti);
		newarti = artifact_upgrade(newarti);

		newbuild.artifacts[newarti.piece] = newarti;

		if (rating(newbuild) > rating(skirk_with_eshu)) {
			skirk_with_eshu = newbuild;
			printf("--------\n");
			printf("new best: artifact %d\n", i);
			artifact_print(newarti);
			printf("score: %g\n", rating(skirk_with_eshu));
			character_print(skirk_with_eshu);
		}
	}



	return 0;
}
