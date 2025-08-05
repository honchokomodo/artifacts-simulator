#include <stdlib.h>
#include <time.h>

#include <assert.h>
static_assert(0, "this file doesnt work atm bc i rewrote a bunch of stuff in character.c");

#include "character.c"

float rating(Character in)
{
	int numOnset = 0;
	for (int i = FLOWER; i <= CIRCLET; i++)
		if (in.artifacts[i].set == ONSET)
			numOnset += 1;

	// Finale of the Deep Galleries 2pc bonus.
	if (numOnset >= 2)
		in.cryo_bonus += 15;

	// Calamity of Eshu passive bonus for normal and charged attacks only.
	in.crit_rate += 16;

	AggregateStats aggregate = character_aggregate_stats(in);
	float score = aggregate.atk * aggregate.crit * (1 + aggregate.cryo_bonus / 100);

	// Finale of the Deep Galleries 4pc bonus.
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
		.crit_rate = 5.0,
		.crit_damage = 88.4,
		.energy_recharge = 100.0,
	};

	int resin_per_day = 180;
	int resin_per_week = resin_per_day * 7 + 60 - 90; // 90 resin used on weekly bosses
	int weeks_farmed = 5;
	int total_resin = resin_per_week * weeks_farmed;

	int claim_cost = 20;
	int total_claims = total_resin / claim_cost;
	float artifacts_per_claim = 1.065;
	int total_artifacts = (int) (total_claims * artifacts_per_claim);
	for (int i = 0; i < total_artifacts; i++) {
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
