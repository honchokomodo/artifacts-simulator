#include <stdlib.h>
#include <stdio.h>

enum stattype {
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
};

char * stat2str[] = {
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

struct stat {
	enum stattype type;
	float value;
};

enum piecetype {
	FLOWER,
	FEATHER,
	SANDS,
	GOBLET,
	CIRCLET,
};

char * piece2str[] = {
	[FLOWER] = "flower",
	[FEATHER] = "feather",
	[SANDS] = "sands",
	[GOBLET] = "goblet",
	[CIRCLET] = "circlet",
};

struct artifact {
	int quality;
	int level;
	enum piecetype piece;
	struct stat mainstat;

	size_t num_substats;
	struct stat substat[4];
};

void printartifact(struct artifact in)
{
	printf("%s\n", piece2str[in.piece]);
	printf("Main stat: %s - %g\n", stat2str[in.mainstat.type], in.mainstat.value);
	for (int i = 0; i < in.num_substats; i++)
		printf("\t%s - %g\n", stat2str[in.substat[i].type], in.substat[i].value);
}

struct choice_weight {
	int choice;
	int weight;
};

int weighted_random_choice(struct choice_weight const * weights, size_t len, int max)
{
	int roll = 1 + rand() % max;
	int accumulator = 0;

	for (int i = 0; i < len; i++) {
		accumulator += weights[i].weight;
		if (roll <= accumulator)
			return weights[i].choice;
	}

	return -1;
}

struct stat get_sands_mainstat(void)
{
	static struct choice_weight const weights[] = {
		{HP_PERCENT, 8},
		{ATK_PERCENT, 8},
		{DEF_PERCENT, 8},
		{ENERGY_RECHARGE, 3},
		{ELEMENTAL_MASTERY, 3},
	};
	static int const max = 30;
	static size_t const len = sizeof(weights) / sizeof(weights[0]);

	struct stat out = {0};
	out.type = weighted_random_choice(weights, len, max);

	return out;
}

struct stat get_goblet_mainstat(void)
{
	static struct choice_weight const weights[] = {
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
	static int const max = 400;
	static size_t const len = sizeof(weights) / sizeof(weights[0]);

	struct stat out = {0};
	out.type = weighted_random_choice(weights, len, max);

	return out;
}

struct stat get_circlet_mainstat(void)
{
	static struct choice_weight const weights[] = {
		{HP_PERCENT, 11},
		{ATK_PERCENT, 11},
		{DEF_PERCENT, 11},
		{CRIT_RATE, 5},
		{CRIT_DAMAGE, 5},
		{HEALING_BONUS, 5},
		{ELEMENTAL_MASTERY, 2},
	};
	static int const max = 50;
	static size_t const len = sizeof(weights) / sizeof(weights[0]);

	struct stat out = {0};
	out.type = weighted_random_choice(weights, len, max);

	return out;
}

void addsubstat(struct artifact * in)
{
	/*
	struct choice_weight weights[] = {
		{HP_FLAT, 6},
		{ATK_FLAT, 6},
		{DEF_FLAT, 6},
		{HP_PERCENT, 4},
		{ATK_PERCENT, 4},
		{DEF_PERCENT, 4},
		{ENERGY_RECHARGE, 4},
		{ELEMENTAL_MASTERY, 4},
		{CRIT_RATE, 3},
		{CRIT_DAMAGE, 3},
	};
	static size_t const len = sizeof(weights) / sizeof(weights[0]);
	*/

	int weights[] = {
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

	max -= weights[in->mainstat.type];
	weights[in->mainstat.type] = 0;
	for (int i = 0; i < in->num_substats; i++) {
		max -= weights[in->substat[i].type];
		weights[in->substat[i].type] = 0;
	}

	int roll = rand() % max;

	for (int i = 0; i <= CRIT_DAMAGE; i++) {
		roll -= weights[i];
		if (roll < 0) {
			in->substat[in->num_substats].type = i;
			in->substat[in->num_substats].value = 1;
			in->num_substats += 1;
			break;
		}
	}
}

struct artifact getarti_domain(void)
{
	struct artifact out = {0};

	// choose a random piece
	out.piece = rand() % 5;

	switch (out.piece) {
		case FLOWER:
			out.mainstat.type = HP_FLAT;
			break;
		case FEATHER:
			out.mainstat.type = ATK_FLAT;
			break;
		case SANDS:
			out.mainstat = get_sands_mainstat();
			break;
		case GOBLET:
			out.mainstat = get_goblet_mainstat();
			break;
		case CIRCLET:
			out.mainstat = get_circlet_mainstat();
			break;
	}

	addsubstat(&out);
	addsubstat(&out);
	addsubstat(&out);
	addsubstat(&out);

	return out;
}

