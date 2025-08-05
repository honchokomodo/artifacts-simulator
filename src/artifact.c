#ifndef ARTIFACT_C
#define ARTIFACT_C

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "common.h"

#define MAX_SUBSTATS 4
#define MAX_UPGRADES 5

typedef enum piece_type {
	PIECE_NOTHING,
	FLOWER,
	FEATHER,
	SANDS,
	GOBLET,
	CIRCLET,
} PieceType;

typedef enum artifact_set {
	SET_NOTHING,
	OFFSET,
	ONSET,
	FINALE_OF_THE_DEEP_GALLERIES,
	MARECHAUSSEE_HUNTER,
	WANDERERS_TROUPE,
} ArtifactSet;

typedef struct affix {
	StatType type;
	float value;
} Affix;

typedef struct artifact {
	int level;
	ArtifactSet set;
	PieceType piece;
	Affix mainstat;

	size_t num_substats;
	Affix substat[MAX_SUBSTATS];
	int num_upgrades[MAX_SUBSTATS];
} Artifact;

/* may not even be necesssary
typedef struct artifact_loadout {
	Artifact flower;
	Artifact feather;
	Artifact sands;
	Artifact goblet;
	Artifact circlet;
} ArtifactLoadout;
*/

char const * const piece2str[] = {
	[PIECE_NOTHING] = "nil piece",
	[FLOWER] = "Flower",
	[FEATHER] = "Feather",
	[SANDS] = "Sands",
	[GOBLET] = "Goblet",
	[CIRCLET] = "Circlet",
};

char const * const set2str[] = {
	[SET_NOTHING] = "nil set",
	[OFFSET] = "offset",
	[ONSET] = "onset",
	[FINALE_OF_THE_DEEP_GALLERIES] = "Finale of the Deep Galleries",
	[MARECHAUSSEE_HUNTER] = "Marechaussee Hunter",
	[WANDERERS_TROUPE] = "Wanderer's Troupe",
};

#include "artifact_set_bonuses.c"

float const mainstat_values[][6] = {
	// values obtained from wiki.
	// table has entries for levels 0, 4, 8, 12, 16, 20.
	[HP_FLAT] = {717, 1530, 2342, 3155, 3967, 4780},
	[ATK_FLAT] = {47, 100, 152, 205, 258, 311},

	[HP_PERCENT] = {7, 14.9, 22.8, 30.8, 38.7, 46.6},
	[ATK_PERCENT] = {7, 14.9, 22.8, 30.8, 38.7, 46.6},

	[DEF_PERCENT] = {8.7, 18.6, 28.6, 38.5, 48.4, 58.3},
	[PHYSICAL_BONUS] = {8.7, 18.6, 28.6, 38.5, 48.4, 58.3},

	[PYRO_BONUS] = {7, 14.9, 22.8, 30.8, 38.7, 46.6},
	[ELECTRO_BONUS] = {7, 14.9, 22.8, 30.8, 38.7, 46.6},
	[CRYO_BONUS] = {7, 14.9, 22.8, 30.8, 38.7, 46.6},
	[HYDRO_BONUS] = {7, 14.9, 22.8, 30.8, 38.7, 46.6},
	[DENDRO_BONUS] = {7, 14.9, 22.8, 30.8, 38.7, 46.6},
	[ANEMO_BONUS] = {7, 14.9, 22.8, 30.8, 38.7, 46.6},
	[GEO_BONUS] = {7, 14.9, 22.8, 30.8, 38.7, 46.6},

	[ELEMENTAL_MASTERY] = {28, 67.6, 91.4, 123.1, 154.8, 186.5},
	[ENERGY_RECHARGE] = {7.8, 16.6, 25.4, 34.2, 43, 51.8},
	[CRIT_RATE] = {4.7, 9.9, 15.2, 20.5, 25.8, 31.1},
	[CRIT_DAMAGE] = {9.3, 19.9, 30.5, 41, 51.6, 62.2},
	[HEALING_BONUS] = {5.4, 11.5, 17.6, 23.7, 29.8, 35.9},
};

float const substat_values[] = {
	// values obtained from wiki.
	// table has entries for max roll only.
	[HP_FLAT] = 298.75,
	[ATK_FLAT] = 19.45,
	[DEF_FLAT] = 23.15,
	[HP_PERCENT] = 5.83,
	[ATK_PERCENT] = 5.83,
	[DEF_PERCENT] = 7.29,
	[ENERGY_RECHARGE] = 6.48,
	[ELEMENTAL_MASTERY] = 23.31,
	[CRIT_RATE] = 3.89,
	[CRIT_DAMAGE] = 7.77,
};

void artifact_print(Artifact in);
Artifact artifact_upgrade_newline(Artifact in, StatType type, float rv);
Artifact artifact_upgrade_line(Artifact in, int line, float rv);
Artifact artifact_upgrade(Artifact in);

#define ARTIFACT_NEW(has4substats, ...) artifact_new(has4substats, (Artifact) {__VA_ARGS__})
Artifact artifact_new(bool has4substats, Artifact in);
Artifact artifact_new_domain(ArtifactSet set1, ArtifactSet set2);
Artifact artifact_new_strongbox(ArtifactSet set);

void artifact_print(Artifact in)
{
	/*
	static int const percent_bitmask = 0xfff54;
	static char const * const pct[] = {"", "%"};
	*/

	printf("%s - %s +%d\n", set2str[in.set], piece2str[in.piece], in.level);
	/*
	printf("%-23s%8g%s\n", stat2str[in.mainstat.type], in.mainstat.value, pct[percent_bitmask >> in.mainstat.type & 1]);
	for (int i = 0; i < in.num_substats; i++) {
		printf(" %d %-20s%8g%s\n", in.num_upgrades[i], stat2str[in.substat[i].type], in.substat[i].value, pct[percent_bitmask >> in.substat[i].type & 1]);
		*/
	printf("%-23s%8g%s\n", stat2str[in.mainstat.type], in.mainstat.value, stat2pct[in.mainstat.type]);
	for (int i = 0; i < in.num_substats; i++) {
		printf(" %d %-20s%8g%s\n", in.num_upgrades[i], stat2str[in.substat[i].type], in.substat[i].value, stat2pct[in.substat[i].type]);
	}
}

Artifact _artifact_addsubstat(Artifact in)
{
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
	max -= substat_weights[in.mainstat.type];
	substat_weights[in.mainstat.type] = 0;
	for (int i = 0; i < in.num_substats; i++) {
		max -= substat_weights[in.substat[i].type];
		substat_weights[in.substat[i].type] = 0;
	}

	int roll = 1 + rand() % max;
	int accumulator = 0;
	float rv = (rand() % 4) * 0.1 + 0.7;

	for (int i = 0; i <= CRIT_DAMAGE; i++) {
		accumulator += substat_weights[i];
		if (roll <= accumulator) {
			in.substat[in.num_substats].type = i;
			in.substat[in.num_substats].value = rv * substat_values[i];
			in.num_substats += 1;
			break;
		}
	}

	return in;
}

Artifact artifact_upgrade_newline(Artifact in, StatType type, float rv)
{
	in.level += 4;
	in.mainstat.value = mainstat_values[in.mainstat.type][in.level / 4];

	int line = in.num_substats;
	in.substat[line].type = type;
	in.substat[line].value = rv * substat_values[type];
	in.num_substats += 1;

	return in;
}

Artifact artifact_upgrade_line(Artifact in, int line, float rv)
{
	in.level += 4;
	in.mainstat.value = mainstat_values[in.mainstat.type][in.level / 4];

	StatType type = in.substat[line].type;
	in.substat[line].value += rv * substat_values[type];
	in.num_upgrades[line] += 1;

	return in;
}

Artifact artifact_upgrade(Artifact in)
{
	if (in.level >= 20)
		return in;

	in.level += 4;
	in.mainstat.value = mainstat_values[in.mainstat.type][in.level / 4];

	if (in.num_substats < 4)
		return _artifact_addsubstat(in);

	int line = rand() % 4;
	float rv = (rand() % 4) * 0.1 + 0.7;
	StatType type = in.substat[line].type;
	in.substat[line].value += rv * substat_values[type];
	in.num_upgrades[line] += 1;

	return in;
}

StatType _artifact_getmainstat(PieceType piece)
{
	typedef struct choice {
		StatType choice;
		int weight;
	} Choice;

	static int const max = 10000;

	static Choice const flower_weights[] = {
		// only 1 possible choice.
		{HP_FLAT, max},
	};

	static Choice const feather_weights[] = {
		// only 1 possible choice.
		{ATK_FLAT, max},
	};

	static Choice const sands_weights[] = {
		// weights obtained from wiki.
		{HP_PERCENT, 2668},
		{ATK_PERCENT, 2666},
		{DEF_PERCENT, 2666},
		{ENERGY_RECHARGE, 1000},
		{ELEMENTAL_MASTERY, 1000},
	};

	static Choice const goblet_weights[] = {
		// weights obtained from wiki.
		{HP_PERCENT, 1925},
		{ATK_PERCENT, 1925},
		{DEF_PERCENT, 1900},
		{PYRO_BONUS, 500},
		{ELECTRO_BONUS, 500},
		{CRYO_BONUS, 500},
		{HYDRO_BONUS, 500},
		{DENDRO_BONUS, 500},
		{ANEMO_BONUS, 500},
		{GEO_BONUS, 500},
		{PHYSICAL_BONUS, 500},
		{ELEMENTAL_MASTERY, 250},
	};

	static Choice const circlet_weights[] = {
		// weights obtained from wiki.
		{HP_PERCENT, 2200},
		{ATK_PERCENT, 2200},
		{DEF_PERCENT, 2200},
		{CRIT_RATE, 1000},
		{CRIT_DAMAGE, 1000},
		{HEALING_BONUS, 1000},
		{ELEMENTAL_MASTERY, 400},
	};

	static Choice const * const weights[] = {
		[FLOWER] = flower_weights,
		[FEATHER] = feather_weights,
		[SANDS] = sands_weights,
		[GOBLET] = goblet_weights,
		[CIRCLET] = circlet_weights,
	};

	static size_t const len[] = {
		[FLOWER] = sizeof(flower_weights) / sizeof(flower_weights[0]),
		[FEATHER] = sizeof(feather_weights) / sizeof(feather_weights[0]),
		[SANDS] = sizeof(sands_weights) / sizeof(sands_weights[0]),
		[GOBLET] = sizeof(goblet_weights) / sizeof(goblet_weights[0]),
		[CIRCLET] = sizeof(circlet_weights) / sizeof(circlet_weights[0]),
	};

	int mainstat_roll = 1 + rand() % max;
	int accumulator = 0;

	for (int i = 0; i < len[piece]; i++) {
		accumulator += weights[piece][i].weight;
		if (mainstat_roll <= accumulator) {
			return weights[piece][i].choice;
		}
	}

	return STAT_NOTHING;
}

Artifact artifact_new(bool has4substats, Artifact in)
{
	// ignore artifact set. assume it is properly initialized
	
	// determine which piece the arti will be
	if (in.piece == PIECE_NOTHING)
		in.piece = 1 + rand() % 5;

	// determine which mainstat the artifact will have
	if (in.mainstat.type == STAT_NOTHING)
		in.mainstat.type = _artifact_getmainstat(in.piece);

	if (in.mainstat.value == 0)
		in.mainstat.value = mainstat_values[in.mainstat.type][in.level / 4];
	
	// determine what substats the artifact will have
	int substats = 3;
	if (has4substats)
		substats = 4;

	while (in.num_substats < substats)
		in = _artifact_addsubstat(in);

	int num_upgrades = in.level / 4;
	in.level = 0;
	for (int i = 0; i < num_upgrades; i++)
		in = artifact_upgrade(in);

	return in;
}

Artifact artifact_new_domain(ArtifactSet set1, ArtifactSet set2)
{
	Artifact arti = {.set = rand() % 2 != 0 ? set1 : set2};
	return artifact_new(rand() % 5 == 0, arti);
}

Artifact artifact_new_strongbox(ArtifactSet set)
{
	Artifact arti = {.set = set};
	return artifact_new(rand() % 3 == 0, arti);
}

#endif
