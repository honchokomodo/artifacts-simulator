#ifndef ARTIFACT_SET_BONUSES_C
#define ARTIFACT_SET_BONUSES_C

#include "common.h"

void noop_set_bonus_func(
		int num_pieces,
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor)
{
	// this function does nothing
}

void finale_of_the_deep_galleries_set_bonus_func(
		int num_pieces,
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor)
{
	if (num_pieces < 2) return;
	accumulators[CRYO_BONUS] += 15.0;

	if (num_pieces < 4) return;
	*multiplicative_factor *= 1.6;
}

void marechaussee_hunter_set_bonus_func(
		int num_pieces,
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor)
{
	// this function does nothing
	// TODO: implement this
}

void wanderers_troupe_set_bonus_func(
		int num_pieces,
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor)
{
	// this function does nothing
	// TODO: implement this
}

typedef void (*SetBonusHandlerFunc)(
		int num_pieces,
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor);

SetBonusHandlerFunc const set2bonusfunc[] = {
	[SET_NOTHING] = noop_set_bonus_func,
	[OFFSET] = noop_set_bonus_func,
	[ONSET] = noop_set_bonus_func,
	[FINALE_OF_THE_DEEP_GALLERIES] = finale_of_the_deep_galleries_set_bonus_func,
	[MARECHAUSSEE_HUNTER] = marechaussee_hunter_set_bonus_func,
	[WANDERERS_TROUPE] = wanderers_troupe_set_bonus_func,
};

void handle_artifact_set_bonuses(
		ArtifactSet set,
		int num_pieces,
		float accumulators[CRIT_DAMAGE + 1],
		float * multiplicative_factor)
{
	set2bonusfunc[set](num_pieces, accumulators, multiplicative_factor);
}

#endif
