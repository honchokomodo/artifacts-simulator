#ifndef COMMON_H
#define COMMON_H

#include <stdio.h> // for printf. get rid of this

typedef enum stattype {
	STAT_NOTHING,
	HP_FLAT,
	ATK_FLAT,
	DEF_FLAT,
	HP_PERCENT,
	ATK_PERCENT,
	DEF_PERCENT,
	ELEMENTAL_MASTERY,
	ENERGY_RECHARGE,
	CRIT_RATE,
	CRIT_DAMAGE,
	PYRO_BONUS,
	ELECTRO_BONUS,
	CRYO_BONUS,
	HYDRO_BONUS,
	DENDRO_BONUS,
	ANEMO_BONUS,
	GEO_BONUS,
	PHYSICAL_BONUS,
	HEALING_BONUS,
	HP_BASE,
	ATK_BASE,
	DEF_BASE,
	HP_AGGREGATE,
	ATK_AGGREGATE,
	DEF_AGGREGATE,
	BONUS_DAMAGE,
	DAMAGE_MULTIPLIER,
	DAMAGE_ADDITIVE,
	STAT_COUNT,
} StatType;

char const * const stat2str[STAT_COUNT] = {
	[STAT_NOTHING] = "nil stat",
	[HP_FLAT] = "HP",
	[ATK_FLAT] = "ATK",
	[DEF_FLAT] = "DEF",
	[HP_PERCENT] = "HP%",
	[ATK_PERCENT] = "ATK%",
	[DEF_PERCENT] = "DEF%",
	[ELEMENTAL_MASTERY] = "Elemental Mastery",
	[ENERGY_RECHARGE] = "Energy Recharge",
	[CRIT_RATE] = "CRIT Rate",
	[CRIT_DAMAGE] = "CRIT DMG",
	[PYRO_BONUS] = "Pyro DMG Bonus",
	[ELECTRO_BONUS] = "Electro DMG Bonus",
	[CRYO_BONUS] = "Cryo DMG Bonus",
	[HYDRO_BONUS] = "Hydro DMG Bonus",
	[DENDRO_BONUS] = "Dendro DMG Bonus",
	[ANEMO_BONUS] = "Anemo DMG Bonus",
	[GEO_BONUS] = "Geo DMG Bonus",
	[PHYSICAL_BONUS] = "Physical DMG Bonus",
	[HEALING_BONUS] = "Healing Bonus",
	[HP_BASE] = "Base HP",
	[ATK_BASE] = "Base ATK",
	[DEF_BASE] = "Base DEF",
	[HP_AGGREGATE] = "HP",
	[ATK_AGGREGATE] = "ATK",
	[DEF_AGGREGATE] = "DEF",
	[BONUS_DAMAGE] = "DMG Bonus",
	[DAMAGE_MULTIPLIER] = "Base DMG Multipiler",
	[DAMAGE_ADDITIVE] = "Additive Base DMG",
};

char const * const stat2abbr[STAT_COUNT] = {
	[STAT_NOTHING] = "nil",
	[HP_FLAT] = "HP",
	[ATK_FLAT] = "ATK",
	[DEF_FLAT] = "DEF",
	[HP_PERCENT] = "HP%",
	[ATK_PERCENT] = "ATK%",
	[DEF_PERCENT] = "DEF%",
	[ELEMENTAL_MASTERY] = "EM",
	[ENERGY_RECHARGE] = "ER",
	[CRIT_RATE] = "CR",
	[CRIT_DAMAGE] = "CD",
	[PYRO_BONUS] = "Pyr.",
	[ELECTRO_BONUS] = "Ele.",
	[CRYO_BONUS] = "Cry.",
	[HYDRO_BONUS] = "Hyd.",
	[DENDRO_BONUS] = "Den.",
	[ANEMO_BONUS] = "Ane.",
	[GEO_BONUS] = "Geo.",
	[PHYSICAL_BONUS] = "Phy.",
	[HEALING_BONUS] = "Hea.",
	[HP_BASE] = "bHP",
	[ATK_BASE] = "bATK",
	[DEF_BASE] = "bDEF",
	[HP_AGGREGATE] = "HP", // identical to HP_FLAT. change?
	[ATK_AGGREGATE] = "ATK", // identical to ATK_FLAT. change?
	[DEF_AGGREGATE] = "DEF", // identical to DEF_FLAT. change?
	[BONUS_DAMAGE]= "Bon.", // this one just sucks
	[DAMAGE_MULTIPLIER] = "mul.",
	[DAMAGE_ADDITIVE] = "add.",
};

char const * const stat2pct[STAT_COUNT] = {
	[STAT_NOTHING] = "",
	[HP_FLAT] = "",
	[ATK_FLAT] = "",
	[DEF_FLAT] = "",
	[HP_PERCENT] = "%",
	[ATK_PERCENT] = "%",
	[DEF_PERCENT] = "%",
	[ELEMENTAL_MASTERY] = "",
	[ENERGY_RECHARGE] = "%",
	[CRIT_RATE] = "%",
	[CRIT_DAMAGE] = "%",
	[PYRO_BONUS] = "%",
	[ELECTRO_BONUS] = "%",
	[CRYO_BONUS] = "%",
	[HYDRO_BONUS] = "%",
	[DENDRO_BONUS] = "%",
	[ANEMO_BONUS] = "%",
	[GEO_BONUS] = "%",
	[PHYSICAL_BONUS] = "%",
	[HEALING_BONUS] = "%",
	[HP_BASE] = "",
	[ATK_BASE] = "",
	[DEF_BASE] = "",
	[HP_AGGREGATE] = "",
	[ATK_AGGREGATE] = "",
	[DEF_AGGREGATE] = "",
	[BONUS_DAMAGE]= "%",
	[DAMAGE_MULTIPLIER] = "%",
	[DAMAGE_ADDITIVE] = "",
};
 
typedef struct stat_accumulators {
	float ar[STAT_COUNT];
} StatAccumulators;

// TODO: probably delete this?
typedef struct buff_element {
	StatAccumulators buff;
	char const * label;
} BuffElement;

// TODO: move this elsewehere
void accumulator_print(StatAccumulators in)
{
	for (int i = 0; i < STAT_COUNT; i++) {
		if (in.ar[i] != 0) { \
			printf("%s - %g\n", stat2str[i], in.ar[i]); \
		}
	}
}

StatAccumulators accumulator_combine(StatAccumulators lhs, StatAccumulators rhs)
{
	for (int stat = 1; stat < STAT_COUNT; stat++) {
		lhs.ar[stat] += rhs.ar[stat];
	}

	return lhs;
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
