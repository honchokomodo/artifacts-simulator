#ifndef COMMON_H
#define COMMON_H

#define MAX_BUFFS 20

typedef enum stattype {
	STAT_NOTHING,
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
	STAT_COUNT,
} StatType;

char const * const stat2str[STAT_COUNT] = {
	[STAT_NOTHING] = "nil stat",
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

char const * const stat2abbr[] = {
	[STAT_NOTHING] = "nil",
	[HP_FLAT] = "HP",
	[HP_PERCENT] = "HP%",
	[ATK_FLAT] = "ATK",
	[ATK_PERCENT] = "ATK%",
	[DEF_FLAT] = "DEF",
	[DEF_PERCENT] = "DEF%",
	[ELEMENTAL_MASTERY] = "EM",
	[ENERGY_RECHARGE] = "ER",
	[PYRO_BONUS] = "Pyr.",
	[ELECTRO_BONUS] = "Ele.",
	[CRYO_BONUS] = "Cry.",
	[HYDRO_BONUS] = "Hyd.",
	[DENDRO_BONUS] = "Den.",
	[ANEMO_BONUS] = "Ane.",
	[GEO_BONUS] = "Geo.",
	[PHYSICAL_BONUS] = "Phy.",
	[HEALING_BONUS] = "Hea.",
	[CRIT_RATE] = "CR",
	[CRIT_DAMAGE] = "CD",
};

char const * const stat2pct[] = {
	[STAT_NOTHING] = "",
	[HP_FLAT] = "",
	[HP_PERCENT] = "%",
	[ATK_FLAT] = "",
	[ATK_PERCENT] = "%",
	[DEF_FLAT] = "",
	[DEF_PERCENT] = "%",
	[ELEMENTAL_MASTERY] = "",
	[ENERGY_RECHARGE] = "%",
	[PYRO_BONUS] = "%",
	[ELECTRO_BONUS] = "%",
	[CRYO_BONUS] = "%",
	[HYDRO_BONUS] = "%",
	[DENDRO_BONUS] = "%",
	[ANEMO_BONUS] = "%",
	[GEO_BONUS] = "%",
	[PHYSICAL_BONUS] = "%",
	[HEALING_BONUS] = "%",
	[CRIT_RATE] = "%",
	[CRIT_DAMAGE] = "%",
};
 
typedef struct stat_accumulators {
	float hp_base;
	float atk_base;
	float def_base;
	float hp;
	float atk;
	float def;
	float all_bonus; // TO BE ADDED TO ELEMENTAL DAMAGE BONUS
	float factor;
	float ar[STAT_COUNT];
} StatAccumulators;

typedef struct buff_element {
	StatAccumulators buff;
	char * label;
} BuffElement;

StatAccumulators accumulator_combine(StatAccumulators lhs, StatAccumulators rhs)
{
	lhs.hp_base += rhs.hp_base;
	lhs.atk_base += rhs.atk_base;
	lhs.def_base += rhs.def_base;
	lhs.all_bonus += rhs.all_bonus;

	lhs.factor *= rhs.factor;

	for (int stat = 0; stat < STAT_COUNT; stat++) {
		lhs.ar[stat] += rhs.ar[stat];
	}

	return lhs;
}

void buff_append(BuffElement * list, size_t * len, BuffElement buff)
{
	if (*len >= MAX_BUFFS) return;
	list[*len++] = buff;
}

void buff_remove(BuffElement * list, size_t * len, int idx)
{
	if (*len <= 0) return;
	if (idx < 0 || idx >= *len) return;

	// just shift everything over
	for (int i = idx + 1; i < *len; i++)
		list[i - 1] = list[i];

	*len -= 1;
}

int check_ascension(int level, int ascension)
{
	int min = 0;
	if (level <= 20) min = 0;
	else if (level <= 40) min = 1;
	else min = (level - 1) / 10 - 2;

	int max = 0;
	if (level < 20) max = 0;
	else if (level < 40) max = 1;
	else max = level / 10 - 2;

	if (ascension <= min) return min;
	if (ascension >= max) return max;
	return ascension;
}

int ascension_max_level(int ascension)
{
	if (ascension <= 0) return 20;
	return (ascension + 3) * 10;
}
#endif
