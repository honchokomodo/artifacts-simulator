#ifndef SCENARIO_C
#define SCENARIO_C

#include "artifact.c"
#include "weapon.c"
#include "character.c"

typedef struct scenario {
	CharacterStats character;
	Weapon weapon;
	ArtifactLoadout loadout;
	StatAccumulators accumulators;
} Scenario;

// should match what is seen idle in-game as closely as possible.
void scenario_print(Scenario in)
{
	// step 1: prepare accumulators
	StatAccumulators accumulators = {
		.hp_base = in.character.hp,
		.atk_base = in.character.atk,
		.def_base = in.character.def,
		.ar[HP_PERCENT] = in.character.hp_percent,
		.ar[ATK_PERCENT] = in.character.atk_percent,
		.ar[DEF_PERCENT] = in.character.def_percent,
		.ar[ELEMENTAL_MASTERY] = in.character.elemental_mastery,
		.ar[ENERGY_RECHARGE] = in.character.energy_recharge,
		.ar[PYRO_BONUS] = in.character.pyro_bonus,
		.ar[ELECTRO_BONUS] = in.character.electro_bonus,
		.ar[CRYO_BONUS] = in.character.cryo_bonus,
		.ar[HYDRO_BONUS] = in.character.hydro_bonus,
		.ar[DENDRO_BONUS] = in.character.dendro_bonus,
		.ar[ANEMO_BONUS] = in.character.anemo_bonus,
		.ar[GEO_BONUS] = in.character.geo_bonus,
		.ar[PHYSICAL_BONUS] = in.character.physical_bonus,
		.ar[HEALING_BONUS] = in.character.healing_bonus,
		.ar[CRIT_RATE] = in.character.crit_rate,
		.ar[CRIT_DAMAGE] = in.character.crit_damage,
		
		.factor = 1,
	};

	typedef struct set_entry {
		ArtifactSet set;
		int count;
	} Entry;
	Entry setcounters[5] = {0};

	// step 2: aggregate artifact stats and sets into accumulators
#define AGGREGATE_ARTIFACT_STATS(arti) \
	do { \
		accumulators.ar[arti.mainstat.type] += arti.mainstat.value; \
		for (int line = 0; line < 4; line++) { \
			Affix substat = arti.substat[line]; \
			accumulators.ar[substat.type] += substat.value; \
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

	AGGREGATE_ARTIFACT_STATS(in.loadout.flower);
	AGGREGATE_ARTIFACT_STATS(in.loadout.feather);
	AGGREGATE_ARTIFACT_STATS(in.loadout.sands);
	AGGREGATE_ARTIFACT_STATS(in.loadout.goblet);
	AGGREGATE_ARTIFACT_STATS(in.loadout.circlet);

#undef AGGREGATE_ARTIFACT_STATS
	
	// step 3: handle artifact set bonuses
	for (int i = 0; i < 5; i++) {
		SetBonusArgs set_bonus_args = {
			.set = setcounters[i].set,
			.num_pieces = setcounters[i].count,
			.loadout = &in.loadout,
			.accumulators = &accumulators,
		};

		artifact_set_bonus(set_bonus_args);
	}

	// step 4: handle weapon stats
	accumulators.atk_base += in.weapon.atk;
	accumulators.ar[in.weapon.bonus.type] += in.weapon.bonus.value;

	// step 5: handle weapon passives
	WeaponPassiveArgs weapon_passive_args = {
		.weapon = in.weapon,
		.accumulators = &accumulators,
	};
	weapon_passive(weapon_passive_args);
	
	// step 6: handle character passives and constellations
	CharacterTalentArgs character_talent_args = {
		.character = in.character,
		.accumulators = &accumulators,
	};

	character_talents(character_talent_args);

	// step 7: combine base stats with aggregate stats
	float hp_fac = 1 + accumulators.ar[HP_PERCENT] / 100;
	float atk_fac = 1 + accumulators.ar[ATK_PERCENT] / 100;
	float def_fac = 1 + accumulators.ar[DEF_PERCENT] / 100;

	accumulators.hp = accumulators.hp_base * hp_fac
		+ accumulators.ar[HP_FLAT];
	accumulators.atk = accumulators.atk_base * atk_fac
		+ accumulators.ar[ATK_FLAT];
	accumulators.def = accumulators.def_base * def_fac
		+ accumulators.ar[DEF_FLAT];

	// step 8: print the stats
#define COND_PRINT(fmt, key) \
	do { \
		if (accumulators.ar[key] != 0) \
			printf(fmt, accumulators.ar[key]); \
	} while (0)

	printf("%s - lv.%d\n", character2str[in.character.type], in.character.level);
	printf("HP - %g\n", accumulators.hp);
	printf("ATK - %g\n", accumulators.atk);
	printf("DEF - %g\n", accumulators.def);
	COND_PRINT("Elemental Mastery - %g\n", ELEMENTAL_MASTERY);
	printf("Crit RATE - %g%%\n", accumulators.ar[CRIT_RATE]);
	printf("Crit DMG - %g%%\n", accumulators.ar[CRIT_DAMAGE]);
	COND_PRINT("Healing Bonus - %g%%\n", HEALING_BONUS);
	printf("Energy Recharge - %g%%\n", accumulators.ar[ENERGY_RECHARGE]);
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
	artifact_print(in.loadout.flower);
	printf("\n");
	artifact_print(in.loadout.feather);
	printf("\n");
	artifact_print(in.loadout.sands);
	printf("\n");
	artifact_print(in.loadout.circlet);
	printf("\n");
	artifact_print(in.loadout.goblet);
	printf("\n");
}

#endif
