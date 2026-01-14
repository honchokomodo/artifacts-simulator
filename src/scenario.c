#ifndef SCENARIO_C
#define SCENARIO_C

#include "artifact.c"
#include "weapon.c"
#include "character.c"

typedef struct scenario {
	CharacterStats character;
	Weapon weapon;
	ArtifactLoadout loadout;
	StatAccumulators buffs;
} Scenario;

StatAccumulators acc_character_stats(StatAccumulators in,
		CharacterStats character)
{
	return accumulator_combine(in, character.stats);
}

StatAccumulators acc_weapon_stats(StatAccumulators in, Weapon weapon)
{
	in.ar[ATK_BASE] += weapon.atk;
	in.ar[weapon.bonus.type] += weapon.bonus.value;

	return in;
}

StatAccumulators acc_artifact_stats(StatAccumulators in, Artifact artifact)
{
	in.ar[artifact.mainstat.type] += artifact.mainstat.value;
	for (int line = 0; line < artifact.num_substats; line++) {
		Affix substat = artifact.substat[line];
		in.ar[substat.type] += substat.value;
	}

	return in;
}

StatAccumulators compute_base_stats(StatAccumulators in)
{
	float hp_fac = 1 + in.ar[HP_PERCENT] / 100;
	float atk_fac = 1 + in.ar[ATK_PERCENT] / 100;
	float def_fac = 1 + in.ar[DEF_PERCENT] / 100;

	in.ar[HP_AGGREGATE] = in.ar[HP_BASE] * hp_fac + in.ar[HP_FLAT];
	in.ar[ATK_AGGREGATE] = in.ar[ATK_BASE] * atk_fac + in.ar[ATK_FLAT];
	in.ar[DEF_AGGREGATE] = in.ar[DEF_BASE] * def_fac + in.ar[DEF_FLAT];

	return in;
}

StatAccumulators aggregate_stats(Scenario in)
{
	StatAccumulators sto = {0};

	sto = acc_character_stats(sto, in.character);
	sto = acc_weapon_stats(sto, in.weapon);
	sto = acc_artifact_stats(sto, in.loadout.flower);
	sto = acc_artifact_stats(sto, in.loadout.feather);
	sto = acc_artifact_stats(sto, in.loadout.sands);
	sto = acc_artifact_stats(sto, in.loadout.goblet);
	sto = acc_artifact_stats(sto, in.loadout.circlet);
	sto = accumulator_combine(sto, in.buffs);
	sto = compute_base_stats(sto);

	return sto;
}

void scenario_print(Scenario in)
{
	StatAccumulators sto = aggregate_stats(in);

#define COND_PRINT(fmt, key) \
	do { \
		if (sto.ar[key] != 0) \
			printf(fmt, sto.ar[key]); \
	} while (0)

	printf("%s - lv.%d\n", character2str[in.character.type], in.character.level);
	COND_PRINT("HP - %g\n", HP_AGGREGATE);
	COND_PRINT("ATK - %g\n", ATK_AGGREGATE);
	COND_PRINT("DEF - %g\n", DEF_AGGREGATE);
	COND_PRINT("Elemental Mastery - %g\n", ELEMENTAL_MASTERY);
	COND_PRINT("Crit RATE - %g%%\n", CRIT_RATE);
	COND_PRINT("Crit DMG - %g%%\n", CRIT_DAMAGE);
	COND_PRINT("Healing Bonus - %g%%\n", HEALING_BONUS);
	COND_PRINT("Energy Recharge - %g%%\n", ENERGY_RECHARGE);
	COND_PRINT("Pyro DMG Bonus - %g%%\n", PYRO_BONUS);
	COND_PRINT("Hydro DMG Bonus - %g%%\n", HYDRO_BONUS);
	COND_PRINT("Dendro DMG Bonus - %g%%\n", DENDRO_BONUS);
	COND_PRINT("Electro DMG Bonus - %g%%\n", ELECTRO_BONUS);
	COND_PRINT("Anemo DMG Bonus - %g%%\n", ANEMO_BONUS);
	COND_PRINT("Cryo DMG Bonus - %g%%\n", CRYO_BONUS);
	COND_PRINT("Geo DMG Bonus - %g%%\n", GEO_BONUS);
	COND_PRINT("Physical DMG Bonus - %g%%\n", PHYSICAL_BONUS);

#undef COND_PRINT

	printf("\n");
	printf("%s - R%d\n", weapon2str[in.weapon.type], in.weapon.refinement);
	printf("ATK - %g\n", in.weapon.atk);
	printf("%s - %g%s\n", stat2str[in.weapon.bonus.type], in.weapon.bonus.value, stat2pct[in.weapon.bonus.type]);

	printf("\n");
	artifact_print(in.loadout.flower);
	printf("\n");
	artifact_print(in.loadout.feather);
	printf("\n");
	artifact_print(in.loadout.sands);
	printf("\n");
	artifact_print(in.loadout.goblet);
	printf("\n");
	artifact_print(in.loadout.circlet);
	printf("\n");
}

typedef enum crit_type {
	MEAN_CRIT,
	ON_CRIT,
	OFF_CRIT,
} CritType;

typedef struct simple_base_damage_args {
	StatType scale_stat;
	float scale_factor;
	StatType elem_bonus;
	CritType crit;
} SimpleDamageArgs;

float simple_base_damage(StatAccumulators sto, SimpleDamageArgs args)
{
	float dmg_bonus_fac = 1 + (sto.ar[BONUS_DAMAGE] + sto.ar[args.elem_bonus]) / 100;
	float base_dmg = sto.ar[args.scale_stat] * args.scale_factor;
	float crit_fac = 1 + sto.ar[CRIT_DAMAGE] / 100;
	float mean_crit_fac = 1 + sto.ar[CRIT_DAMAGE] * sto.ar[CRIT_RATE] / 10000;

	if (args.crit == MEAN_CRIT) {
		return base_dmg * dmg_bonus_fac * mean_crit_fac;
	} else if (args.crit == ON_CRIT) {
		return base_dmg * dmg_bonus_fac * crit_fac;
	}

	return base_dmg * dmg_bonus_fac;
}

float amplifying_damage(StatAccumulators sto, SimpleDamageArgs args)
{
	float dmg_bonus_fac = 1 + (sto.ar[BONUS_DAMAGE] + sto.ar[args.elem_bonus]) / 100;
	float base_dmg = sto.ar[args.scale_stat] * args.scale_factor;
	float crit_fac = 1 + sto.ar[CRIT_DAMAGE] / 100;
	float mean_crit_fac = 1 + sto.ar[CRIT_DAMAGE] * sto.ar[CRIT_RATE] / 10000;
	float em_bonus_fac = 1 + 2.78 * sto.ar[ELEMENTAL_MASTERY]/ (sto.ar[ELEMENTAL_MASTERY] + 1400);
	//TODO: include reaction bonus

	if (args.crit == MEAN_CRIT) {
		return base_dmg * dmg_bonus_fac * mean_crit_fac * em_bonus_fac;
	} else if (args.crit == ON_CRIT) {
		return base_dmg * dmg_bonus_fac * crit_fac * em_bonus_fac;
	}

	return base_dmg * dmg_bonus_fac * em_bonus_fac;
}

/* TODO: transformative reactions
 * requires:
 * elemental mastery
 * reaction bonus
 */
float transformative_damage(StatAccumulators sto)
{
}

/* TODO:
 * aggravate
 * spread
 * 
 * lunar-charged
 * lunar-charged direct
 * lunar-bloom
 */

#endif
