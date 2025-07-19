#include <stdlib.h>
#include <stdio.h>

typedef enum stattype {
	HP_FLAT,
	HP_PERCENT,
	ATK_FLAT,
	ATK_PERCENT,
	DEF_FLAT,
	DEF_PERCENT,
	ELEMENTAL_MASTERY,
	ENERGY_RECHARGE,
	PYRO_BONUS,
	ELECTRO_BONUS,
	CRYO_BONUS,
	HYDRO_BONUS,
	DENDRO_BONUS,
	ANEMO_BONUS,
	GEO_BONUS,
	PHYSICAL_BONUS,
	HEALING_BONUS,
	CRIT_RATE,
	CRIT_DAMAGE,
} StatType;

typedef enum piecetype {
	FLOWER,
	FEATHER,
	SANDS,
	GOBLET,
	CIRCLET,
} PieceType;

typedef enum artifactset {
	OFFSET,
	ONSET,
} ArtifactSet;

typedef struct affix {
	float value;
	StatType type;
} Affix;

typedef struct artifact {
	int level;
	ArtifactSet set;
	PieceType piece;
	Affix mainstat;

	size_t num_substats;
	Affix substat[4];
} Artifact;

char const * const stat2str[] = {
	[HP_FLAT] = "HP",
	[HP_PERCENT] = "HP%",
	[ATK_FLAT] = "ATK",
	[ATK_PERCENT] = "ATK%",
	[DEF_FLAT] = "DEF",
	[DEF_PERCENT] = "DEF%",
	[ELEMENTAL_MASTERY] = "Elemental Mastery",
	[ENERGY_RECHARGE] = "Energy Recharge",
	[PYRO_BONUS] = "Pyro DMG Bonus",
	[ELECTRO_BONUS] = "Electro DMG Bonus",
	[CRYO_BONUS] = "Cryo DMG Bonus",
	[HYDRO_BONUS] = "Hydro DMG Bonus",
	[DENDRO_BONUS] = "Dendro DMG Bonus",
	[ANEMO_BONUS] = "Anemo DMG Bonus",
	[GEO_BONUS] = "Geo DMG Bonus",
	[PHYSICAL_BONUS] = "Physical DMG Bonus",
	[HEALING_BONUS] = "Healing Bonus",
	[CRIT_RATE] = "CRIT Rate",
	[CRIT_DAMAGE] = "CRIT DMG",
};

char const * const piece2str[] = {
	[FLOWER] = "Flower",
	[FEATHER] = "Feather",
	[SANDS] = "Sands",
	[GOBLET] = "Goblet",
	[CIRCLET] = "Circlet",
};

char const * const set2str[] = {
	[OFFSET] = "offset",
	[ONSET] = "onset",
};

float const mainstat_values[][6] = {
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

void artifact_print(Artifact in)
{
	static int const percent_bitmask = 0x7ffaa;
	static char const * const pct[] = {"", "%"};

	printf("%s - %s +%d\n", set2str[in.set], piece2str[in.piece], in.level);
	printf("%-23s%8g%s\n", stat2str[in.mainstat.type], in.mainstat.value, pct[percent_bitmask >> in.mainstat.type & 1]);
	for (int i = 0; i < in.num_substats; i++) {
		printf(" - %-20s%8g%s\n", stat2str[in.substat[i].type], in.substat[i].value, pct[percent_bitmask >> in.substat[i].type & 1]);
	}
}

Artifact _artifact_addsubstat(Artifact in)
{
	int substat_weights[] = {
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

Artifact artifact_new(bool has4substats, ArtifactSet set, PieceType piece)
{
	Artifact out = {0};
	
	// determine which set the arti will be on
	out.set = set;

	// determine which piece the arti will be
	out.piece = piece;

	// determine which mainstat the artifact will have
	typedef struct choice {
		int choice;
		int weight;
	} Choice;

	static Choice const flower_weights[] = {
		{HP_FLAT, 1},
	};

	static Choice const feather_weights[] = {
		{ATK_FLAT, 1},
	};

	static Choice const sands_weights[] = {
		{HP_PERCENT, 8},
		{ATK_PERCENT, 8},
		{DEF_PERCENT, 8},
		{ENERGY_RECHARGE, 3},
		{ELEMENTAL_MASTERY, 3},
	};

	static Choice const goblet_weights[] = {
		{HP_PERCENT, 77},
		{ATK_PERCENT, 77},
		{DEF_PERCENT, 76},
		{PYRO_BONUS, 20},
		{ELECTRO_BONUS, 20},
		{CRYO_BONUS, 20},
		{HYDRO_BONUS, 20},
		{DENDRO_BONUS, 20},
		{ANEMO_BONUS, 20},
		{GEO_BONUS, 20},
		{PHYSICAL_BONUS, 20},
		{ELEMENTAL_MASTERY, 10},
	};
	
	static Choice const circlet_weights[] = {
		{HP_PERCENT, 11},
		{ATK_PERCENT, 11},
		{DEF_PERCENT, 11},
		{CRIT_RATE, 5},
		{CRIT_DAMAGE, 5},
		{HEALING_BONUS, 5},
		{ELEMENTAL_MASTERY, 2},
	};

	static Choice const * const weights[] = {
		flower_weights,
		feather_weights,
		sands_weights,
		goblet_weights,
		circlet_weights,
	};
	static int const max[] = {1, 1, 30, 400, 50};
	static size_t const len[] = {
		sizeof(flower_weights) / sizeof(flower_weights[0]),
		sizeof(feather_weights) / sizeof(feather_weights[0]),
		sizeof(sands_weights) / sizeof(sands_weights[0]),
		sizeof(goblet_weights) / sizeof(goblet_weights[0]),
		sizeof(circlet_weights) / sizeof(circlet_weights[0]),
	};

	int mainstat_roll = 1 + rand() % max[piece];
	int accumulator = 0;

	for (int i = 0; i < len[piece]; i++) {
		accumulator += weights[piece][i].weight;
		if (mainstat_roll <= accumulator) {
			out.mainstat.type = weights[piece][i].choice;
			break;
		}
	}

	out.mainstat.value = mainstat_values[out.mainstat.type][0];

	// determine what substats the artifact will have
	out = _artifact_addsubstat(out);
	out = _artifact_addsubstat(out);
	out = _artifact_addsubstat(out);
	if (has4substats)
		out = _artifact_addsubstat(out);

	return out;
}

Artifact artifact_new_domain(void)
{
	return artifact_new(rand() % 5 == 0, rand() % 2, rand() % 5);
}

Artifact artifact_new_strongbox(void)
{
	return artifact_new(rand() % 3 == 0, 1, rand() % 5);
}

Artifact artifact_upgrade_line(Artifact in, int line, float rv)
{
	in.level += 4;
	in.mainstat.value = mainstat_values[in.mainstat.type][in.level / 4];

	StatType type = in.substat[line].type;
	in.substat[line].value += rv * substat_values[type];

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

	return in;
}

