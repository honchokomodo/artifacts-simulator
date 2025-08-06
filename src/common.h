#ifndef COMMON_H
#define COMMON_H

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
} StatType;

char const * const stat2str[] = {
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

// may need to be auto generated.
typedef enum artifact_set {
	SET_NOTHING,
	OFFSET,
	ONSET,
	FINALE_OF_THE_DEEP_GALLERIES,
	MARECHAUSSEE_HUNTER,
	WANDERERS_TROUPE,
} ArtifactSet;

// may need to be auto generated.
char const * const set2str[] = {
	[SET_NOTHING] = "nil set",
	[FINALE_OF_THE_DEEP_GALLERIES] = "Finale of the Deep Galleries",
	[MARECHAUSSEE_HUNTER] = "Marechaussee Hunter",
	[WANDERERS_TROUPE] = "Wanderer's Troupe",
};

// may need to be auto generated.
/*
typedef enum character_type  {
	CHARACTER_NOTHING,
	AMBER,
	SKIRK,
	YOIMIYA,
} CharacterType;
*/

#include "../build/include/characters_enum.h"

#endif
