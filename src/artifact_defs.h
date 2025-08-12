#ifndef ARTIFACT_DEFS_H
#define ARTIFACT_DEFS_H

#include "common.h"
#include "../build/include/artifacts_enum.h"

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

char const * const piece2str[] = {
	[PIECE_NOTHING] = "nil piece",
	[FLOWER] = "Flower",
	[FEATHER] = "Feather",
	[SANDS] = "Sands",
	[GOBLET] = "Goblet",
	[CIRCLET] = "Circlet",
};

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

typedef struct artifact_loadout {
	Artifact flower;
	Artifact feather;
	Artifact sands;
	Artifact goblet;
	Artifact circlet;
	int bonus1;
	int bonus2;
} ArtifactLoadout;

typedef struct set_bonus_args {
	ArtifactSet set;
	int num_pieces;
	ArtifactLoadout * loadout;
	StatAccumulators * accumulators;
} SetBonusArgs;

typedef void (*SetBonusFunc)(SetBonusArgs in);
void noop_set_bonus_func(SetBonusArgs in)
{
	// do nothing
}

#endif
