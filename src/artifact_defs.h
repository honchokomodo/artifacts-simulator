#ifndef ARTIFACT_DEFS_H
#define ARTIFACT_DEFS_H

#include "common.h"
// include artifacts enum

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

// may need to be auto generated.
typedef enum artifact_set {
	SET_NOTHING,
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

#endif
