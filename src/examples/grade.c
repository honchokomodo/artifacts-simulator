#include <stdlib.h>
#include <time.h>

#include "character.c"

float rating(Character in)
{
	int numOnset = 0;
	for (int i = FLOWER; i <= CIRCLET; i++)
		if (in.artifacts[i].set == ONSET)
			numOnset += 1;

	if (numOnset >= 2) {
		// Finale of the Deep Galleries 2pc bonus.
		//in.cryo_bonus += 15;
		// Wanderer's troupe 2pc bonus.
		in.elemental_mastery += 80;
	}

	// Calamity of Eshu passive bonus for normal and charged attacks only.
	//in.crit_rate += 16;
	// Skyward Harp passive bonus.
	in.crit_damage += 20;

	AggregateStats aggregate = character_aggregate_stats(in);
	//float score = aggregate.atk * aggregate.crit * (1 + aggregate.cryo_bonus / 100);
	float em_bonus = 2.78 * aggregate.elemental_mastery / (aggregate.elemental_mastery + 1400);
	float multiplier = 2 * (1 + em_bonus);
	float score = aggregate.atk * aggregate.crit * (1 + aggregate.pyro_bonus / 100) * multiplier;

	if (numOnset >= 4) {
		// Finale of the Deep Galleries 4pc bonus.
		//score *= 1.6;
		// Wanderer's troupe 4pc bonus.
		score *= 1.35;
	}

	return score;
}

float grade(Artifact arti, Character in, float ratingtobeat)
{
	Character newbuild = in;
	// immediately set the mainstat to max value.
	arti.mainstat.value = mainstat_values[arti.mainstat.type][5];
	newbuild.artifacts[arti.piece] = arti;
	float newrating = rating(newbuild);
	float sum = 0;

	// if the artifact already beats the current build, just return
	if (newrating >= ratingtobeat) {
		return 1;
	}

	// if the artifact is max level, just test and return
	if (arti.level >= 20) {
		return newrating >= ratingtobeat;
	}

	// if the artifact is upgradable, check all possible upgrades
	if (arti.num_substats == 4) {
		for (int i = 0; i < arti.num_substats; i++) {
			float substatsum = 0;
			for (int j = 0; j < 4; j++) {
				Artifact newarti = artifact_upgrade_line(arti, i, j * 0.1 + 0.7);
				substatsum += grade(newarti, in, ratingtobeat);
			}
			sum += substatsum;
		}
		return sum / 16;
	}

	// if the artifact is missing a substat, check all possible substats
	if (arti.num_substats < 4) {
		/* ==== this section copied from artifact.c ====*/
		int substat_weights[] = {
			// values obtained from wiki.
			[HP_FLAT] = 6,
			[ATK_FLAT] = 6,
			[DEF_FLAT] = 6,
			[HP_PERCENT] = 4,
			[ATK_PERCENT] = 4,
			[DEF_PERCENT] = 4,
			[ENERGY_RECHARGE] = 4,
			[ELEMENTAL_MASTERY] = 4,
			[CRIT_RATE] = 3,
			[CRIT_DAMAGE] = 3,
		};
		int max = 44;

		// new substats may not match whatever stats are already present.
		max -= substat_weights[arti.mainstat.type];
		substat_weights[arti.mainstat.type] = 0;
		for (int i = 0; i < arti.num_substats; i++) {
			max -= substat_weights[arti.substat[i].type];
			substat_weights[arti.substat[i].type] = 0;
		}
		/* ==== end section copied from artifact.c ====*/

		for (int i = 0; i <= CRIT_DAMAGE; i++) {
			if (substat_weights[i] == 0) {
				continue;
			}

			float substatsum = 0;
			for (int j = 0; j < 4; j++) {
				Artifact newarti = artifact_upgrade_newline(arti, i, j * 0.1 + 0.7);
				substatsum += grade(newarti, in, ratingtobeat);
			}
			sum += substatsum * substat_weights[i];
		}
		return sum / (4 * max);
	}

	return 0;
}

int main(void)
{
	srand(time(NULL));

	Character amber_with_skyward = {
		.name = "Amber with Skyward Harp",
		.hp = 9461,
		.atk = 897,
		.atk_percent = 24.0,
		.def = 601,
		.crit_rate = 27.1,
		.crit_damage = 70.0,
		.energy_recharge = 100.0,

		.artifacts[FLOWER] = {
			.level = 20, .set = ONSET, .piece = FLOWER,
			.num_substats = 4,
			.mainstat = {HP_FLAT, 4780},
			.substat[0] = {CRIT_RATE, 7.8},
			.substat[1] = {ATK_PERCENT, 15.7},
			.substat[2] = {ELEMENTAL_MASTERY, 56},
			.substat[3] = {CRIT_DAMAGE, 7.0},
		},

		.artifacts[FEATHER] = {
			.level = 20, .set = ONSET, .piece = FEATHER,
			.num_substats = 4,
			.mainstat = {ATK_FLAT, 311},
			.substat[0] = {HP_PERCENT, 5.8},
			.substat[1] = {ELEMENTAL_MASTERY, 35},
			.substat[2] = {CRIT_DAMAGE, 17.1},
			.substat[3] = {CRIT_RATE, 10.9},
		},

		.artifacts[SANDS] = {
			.level = 20, .set = ONSET, .piece = SANDS,
			.num_substats = 4,
			.mainstat = {ELEMENTAL_MASTERY, 187},
			.substat[0] = {DEF_FLAT, 16},
			.substat[1] = {CRIT_RATE, 5.4},
			.substat[2] = {ATK_PERCENT, 9.9},
			.substat[3] = {CRIT_DAMAGE, 19.4},
		},

		.artifacts[GOBLET] = {
			.level = 20, .set = OFFSET, .piece = GOBLET,
			.num_substats = 4,
			.mainstat = {PYRO_BONUS, 46.6},
			.substat[0] = {ELEMENTAL_MASTERY, 37},
			.substat[1] = {CRIT_RATE, 5.4},
			.substat[2] = {CRIT_DAMAGE, 21.0},
			.substat[3] = {HP_PERCENT, 10.5},
		},

		.artifacts[CIRCLET] = {
			.level = 20, .set = ONSET, .piece = CIRCLET,
			.num_substats = 4,
			.mainstat = {CRIT_DAMAGE, 62.2},
			.substat[0] = {CRIT_RATE, 10.5},
			.substat[1] = {HP_PERCENT, 15.2},
			.substat[2] = {ELEMENTAL_MASTERY, 16.0},
			.substat[3] = {HP_FLAT, 239},
		},
	};

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

	for (int i = 0; i < 10; i++) {
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
		}

	}
	*/

	character_print(amber_with_skyward);
	printf("\n");

	/*
	Artifact newarti = ARTIFACT_NEW(rand() % 5 == 0, .level = 0, .piece = CIRCLET, .set = ONSET, .mainstat.type = CRIT_DAMAGE);
	*/

	Artifact newarti = {
		.set = ONSET, .piece = SANDS,
		.num_substats = 4,
		.mainstat = {ELEMENTAL_MASTERY, 28},
		.substat[0] = {CRIT_DAMAGE, 6.2},
		.substat[1] = {CRIT_RATE, 2.7},
		.substat[2] = {HP_PERCENT, 4.7},
		.substat[3] = {ATK_PERCENT, 5.8},
	};

	/*
	Artifact newarti = {
		.set = ONSET, .piece = CIRCLET,
		.num_substats = 4,
		.mainstat = {CRIT_DAMAGE, 9.3},
		.substat[0] = {HP_PERCENT, 5.8},
		.substat[1] = {ATK_PERCENT, 4.7},
		.substat[2] = {ELEMENTAL_MASTERY, 19},
		.substat[3] = {CRIT_RATE, 2.7},
	};
	*/

	printf("new artifact:\n");
	artifact_print(newarti);
	printf("grade: %f\n", grade(newarti, amber_with_skyward, rating(amber_with_skyward)));

	/*
	for (int i = 0; i < 5; i++) {
		newarti = artifact_upgrade(newarti);
		printf("\n");
		printf("upgraded:\n");
		artifact_print(newarti);
		printf("grade: %f\n", grade(newarti, amber_with_skyward, rating(amber_with_skyward)));
	}
	*/

	return 0;
}
