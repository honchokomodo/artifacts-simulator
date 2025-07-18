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

static float const substat_values[] = {
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
	[FLOWER] = "Flower",
	[FEATHER] = "Feather",
	[SANDS] = "Sands",
	[GOBLET] = "Goblet",
	[CIRCLET] = "Circlet",
};

struct artifact {
	int level;
	enum piecetype piece;
	struct stat mainstat;

	size_t num_substats;
	struct stat substat[4];
};

void printartifact(struct artifact in)
{
	printf("%s - %d\n", piece2str[in.piece], in.level);
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

void set_mainstat_value(struct artifact * in)
{
	in->mainstat.value = mainstat_values[in->mainstat.type][in->level / 4];
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
			float rv = (rand() % 4) * 0.1 + 0.7;
			in->substat[in->num_substats].type = i;
			in->substat[in->num_substats].value = rv * substat_values[i];
			in->num_substats += 1;
			break;
		}
	}
}

void upgrade(struct artifact * in)
{
	if (in->level >= 20)
		return;

	in->level += 4;
	set_mainstat_value(in);

	if (in->num_substats < 4) {
		addsubstat(in);
		return;
	}

	int pick = rand() % 4;
	float rv = (rand() % 4) * 0.1 + 0.7;
	int type = in->substat[pick].type;
	in->substat[pick].value += rv * substat_values[type];
}

struct artifact newartifact(void)
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
	set_mainstat_value(&out);

	return out;
}

struct artifact getarti(int fourliner)
{
	struct artifact out = newartifact();

	addsubstat(&out);
	addsubstat(&out);
	addsubstat(&out);

	if (fourliner)
		addsubstat(&out);

	return out;
}
