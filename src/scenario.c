#ifndef SCENARIO_C
#define SCENARIO_C

#include "artifact.c"
#include "weapon.c"
#include "character.c"

typedef struct scenario {
	CharacterStats character;
	Weapon weapon;

	Artifact flower;
	Artifact feather;
	Artifact sands;
	Artifact goblet;
	Artifact circlet;
	int bonus1;
	int bonus2;
} Scenario;

// should match what is seen idle in-game as closely as possible.
void scenario_print(Scenario in)
{
	// step 1: prepare accumulators
	float accumulators[CRIT_DAMAGE + 1] = {0};

	float hp_base = in.character.hp;
	float atk_base = in.character.atk;
	float def_base = in.character.def;
	accumulators[HP_PERCENT] += in.character.hp_percent;
	accumulators[ATK_PERCENT] += in.character.atk_percent;
	accumulators[DEF_PERCENT] += in.character.def_percent;
	accumulators[ELEMENTAL_MASTERY] += in.character.elemental_mastery;
	accumulators[ENERGY_RECHARGE] += in.character.energy_recharge;
	accumulators[PYRO_BONUS] += in.character.pyro_bonus;
	accumulators[ELECTRO_BONUS] += in.character.electro_bonus;
	accumulators[CRYO_BONUS] += in.character.cryo_bonus;
	accumulators[HYDRO_BONUS] += in.character.hydro_bonus;
	accumulators[DENDRO_BONUS] += in.character.dendro_bonus;
	accumulators[ANEMO_BONUS] += in.character.anemo_bonus;
	accumulators[GEO_BONUS] += in.character.geo_bonus;
	accumulators[PHYSICAL_BONUS] += in.character.physical_bonus;
	accumulators[HEALING_BONUS] += in.character.healing_bonus;
	accumulators[CRIT_RATE] += in.character.crit_rate;
	accumulators[CRIT_DAMAGE] += in.character.crit_damage;

	typedef struct set_entry {
		ArtifactSet set;
		int count;
	} Entry;
	Entry setcounters[5] = {0};

	float multiplicative_factor = 1;

	// step 2: aggregate artifact stats and sets into accumulators
#define AGGREGATE_ARTIFACT_STATS(arti) \
	do { \
		accumulators[arti.mainstat.type] += arti.mainstat.value; \
		for (int line = 0; line < 4; line++) { \
			Affix substat = arti.substat[line]; \
			accumulators[substat.type] += substat.value; \
		} \
		for (int i = 0; i < 5; i++) { \
			if (setcounters[i].set == SET_NOTHING) { \
				setcounters[i].set = arti.set; \
			} \
			if (setcounters[i].set == arti.set) { \
				setcounters[i].count += 1; \
				break; \
			} \
		} \
	} while (0)

	AGGREGATE_ARTIFACT_STATS(in.flower);
	AGGREGATE_ARTIFACT_STATS(in.feather);
	AGGREGATE_ARTIFACT_STATS(in.sands);
	AGGREGATE_ARTIFACT_STATS(in.goblet);
	AGGREGATE_ARTIFACT_STATS(in.circlet);

#undef AGGREGATE_ARTIFACT_STATS
	
	// step 3: handle artifact set bonuses
	for (int i = 0; i < 5; i++) {
		SetBonusArgs set_bonus_args = {
			.set = setcounters[i].set,
			.num_pieces = setcounters[i].count,
			.accumulators = accumulators,
			.factor = &multiplicative_factor,
			.bonus1 = &in.bonus1,
			.bonus2 = &in.bonus2,
		};

		artifact_set_bonus(set_bonus_args);
	}

	// step 4: handle weapon stats
	atk_base += in.weapon.atk;
	accumulators[in.weapon.bonus.type] += in.weapon.bonus.value;

	// step 5: handle weapon passives
	WeaponPassiveArgs weapon_passive_args = {
		.weapon = in.weapon,
		.accumulators = accumulators,
		.factor = &multiplicative_factor,
	};
	weapon_passive(weapon_passive_args);
	
	// step 6: handle character passives and constellations
	CharacterTalentArgs character_talent_args = {
		.character = in.character,
		.accumulators = accumulators,
		.hp_base = &hp_base,
		.atk_base = &atk_base,
		.def_base = &def_base,
		.factor = &multiplicative_factor,
	};

	character_talents(character_talent_args);

	// step 7: combine base stats with aggregate stats
	float hp_fac = 1 + accumulators[HP_PERCENT] / 100;
	float atk_fac = 1 + accumulators[ATK_PERCENT] / 100;
	float def_fac = 1 + accumulators[DEF_PERCENT] / 100;

	float hp = hp_base * hp_fac + accumulators[HP_FLAT];
	float atk = atk_base * atk_fac + accumulators[ATK_FLAT];
	float def = def_base * def_fac + accumulators[DEF_FLAT];

	// step 8: print the stats
#define COND_PRINT(fmt, key) \
	do { \
		if (accumulators[key] != 0) \
			printf(fmt, accumulators[key]); \
	} while (0)

	printf("%s - lv.%d\n", in.character.name, in.character.level);
	printf("HP - %g\n", hp);
	printf("ATK - %g\n", atk);
	printf("DEF - %g\n", def);
	COND_PRINT("Elemental Mastery - %g\n", ELEMENTAL_MASTERY);
	printf("Crit RATE - %g%%\n", accumulators[CRIT_RATE]);
	printf("Crit DMG - %g%%\n", accumulators[CRIT_DAMAGE]);
	COND_PRINT("Healing Bonus - %g%%\n", HEALING_BONUS);
	printf("Energy Recharge - %g%%\n", accumulators[ENERGY_RECHARGE]);
	COND_PRINT("Pyro DMG Bonus - %g%%\n", PYRO_BONUS);
	COND_PRINT("Hydro DMG Bonus - %g%%\n", HYDRO_BONUS);
	COND_PRINT("Dendro DMG Bonus - %g%%\n", DENDRO_BONUS);
	COND_PRINT("Electro DMG Bonus - %g%%\n", ELECTRO_BONUS);
	COND_PRINT("Anemo DMG Bonus - %g%%\n", ANEMO_BONUS);
	COND_PRINT("Cryo DMG Bonus - %g%%\n", CRYO_BONUS);
	COND_PRINT("Geo DMG Bonus - %g%%\n", GEO_BONUS);
	COND_PRINT("Physical DMG Bonus - %g%%\n", PHYSICAL_BONUS);

#undef COND_PRINT

	// step 9: print the weapon and artifacts
	printf("\n");
	printf("%s - R%d\n", in.weapon.name, in.weapon.refinement);
	printf("ATK - %g\n", in.weapon.atk);
	printf("%s - %g%s\n", stat2str[in.weapon.bonus.type], in.weapon.bonus.value, stat2pct[in.weapon.bonus.type]);

	printf("\n");
	artifact_print(in.flower);
	printf("\n");
	artifact_print(in.feather);
	printf("\n");
	artifact_print(in.sands);
	printf("\n");
	artifact_print(in.circlet);
	printf("\n");
	artifact_print(in.goblet);
	printf("\n");
}

#endif
