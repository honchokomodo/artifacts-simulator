#include "artifact.c"

typedef struct character {
	char * name;
	float hp;
	float hp_percent;
	float atk;
	float atk_percent;
	float def;
	float def_percent;
	float elemental_mastery;
	// max stamina
	
	float crit_rate;
	float crit_damage;
	float healing_bonus;
	// incoming healing bonus
	float energy_recharge;
	// cd reduction
	// shield strength
	
	float pyro_bonus;
	// pyro res
	float hydro_bonus;
	// hydro res
	float dendro_bonus;
	// dendro res
	float electro_bonus;
	// electro res
	float anemo_bonus;
	// anemo res
	float cryo_bonus;
	// cryo res
	float geo_bonus;
	// geo res
	float physical_bonus;
	// physical res
	
	Artifact artifacts[5];
} Character;

typedef struct aggregate_stats {
	float hp;
	float atk;
	float def;
	float elemental_mastery;
	float crit; // average crit factor
	float crit_rate;
	float crit_damage;
	float healing_bonus;
	float energy_recharge;

	float pyro_bonus;
	float hydro_bonus;
	float dendro_bonus;
	float electro_bonus;
	float anemo_bonus;
	float cryo_bonus;
	float geo_bonus;
	float physical_bonus;
} AggregateStats;

AggregateStats character_aggregate_stats(Character in)
{
	float accumulators[CRIT_DAMAGE + 1] = {0};

	for (int i = 0; i < 5; i++) {
		Artifact arti = in.artifacts[i];
		Affix mainstat = arti.mainstat;
		accumulators[mainstat.type] += mainstat.value;
		for (int line = 0; line < 4; line++) {
			Affix substat = arti.substat[line];
			accumulators[substat.type] += substat.value;
		}
	}

	accumulators[HP_PERCENT] += in.hp_percent;
	accumulators[ATK_PERCENT] += in.atk_percent;
	accumulators[DEF_PERCENT] += in.def_percent;
	accumulators[CRIT_RATE] += in.crit_rate;
	accumulators[CRIT_DAMAGE] += in.crit_damage;

	AggregateStats out = {
		.hp = in.hp * (1 + accumulators[HP_PERCENT] / 100) + accumulators[HP_FLAT],
		.atk = in.atk * (1 + accumulators[ATK_PERCENT] / 100) + accumulators[ATK_FLAT],
		.def = in.def * (1 + accumulators[DEF_PERCENT] / 100) + accumulators[DEF_FLAT],
		.elemental_mastery = in.elemental_mastery + accumulators[ELEMENTAL_MASTERY],
		.crit = 1 + (accumulators[CRIT_RATE] * accumulators[CRIT_DAMAGE] / 10000),
		.crit_rate = in.crit_rate + accumulators[CRIT_RATE],
		.crit_damage = in.crit_damage + accumulators[CRIT_DAMAGE],
		.healing_bonus = in.healing_bonus + accumulators[HEALING_BONUS],
		.energy_recharge = in.energy_recharge + accumulators[ENERGY_RECHARGE],

		.pyro_bonus = in.pyro_bonus + accumulators[PYRO_BONUS],
		.hydro_bonus = in.hydro_bonus + accumulators[HYDRO_BONUS],
		.dendro_bonus = in.dendro_bonus + accumulators[DENDRO_BONUS],
		.electro_bonus = in.electro_bonus + accumulators[ELECTRO_BONUS],
		.anemo_bonus = in.anemo_bonus + accumulators[ANEMO_BONUS],
		.cryo_bonus = in.cryo_bonus + accumulators[CRYO_BONUS],
		.geo_bonus = in.geo_bonus + accumulators[GEO_BONUS],
		.physical_bonus = in.physical_bonus + accumulators[PHYSICAL_BONUS],
	};

	return out;
}

void character_print(Character in)
{
	AggregateStats aggregate = character_aggregate_stats(in);

	printf("%s\n", in.name);
	printf("HP - %g\n", aggregate.hp);
	printf("ATK - %g\n", aggregate.atk);
	printf("DEF - %g\n", aggregate.def);
	if (aggregate.elemental_mastery != 0)
		printf("Elemental Mastery - %g\n", aggregate.elemental_mastery);
	printf("Crit RATE - %g%%\n", aggregate.crit_rate);
	printf("Crit DMG - %g%%\n", aggregate.crit_damage);
	if (aggregate.healing_bonus != 0)
		printf("Healing Bonus - %g%%\n", aggregate.healing_bonus);
	printf("Energy Recharge - %g%%\n", aggregate.energy_recharge);
	if (aggregate.pyro_bonus != 0)
		printf("Pyro DMG Bonus - %g%%\n", aggregate.pyro_bonus);
	if (aggregate.hydro_bonus != 0)
		printf("Hydro DMG Bonus - %g%%\n", aggregate.hydro_bonus);
	if (aggregate.dendro_bonus != 0)
		printf("Dendro DMG Bonus - %g%%\n", aggregate.dendro_bonus);
	if (aggregate.electro_bonus != 0)
		printf("Electro DMG Bonus - %g%%\n", aggregate.electro_bonus);
	if (aggregate.anemo_bonus != 0)
		printf("Anemo DMG Bonus - %g%%\n", aggregate.anemo_bonus);
	if (aggregate.cryo_bonus != 0)
		printf("Cryo DMG Bonus - %g%%\n", aggregate.cryo_bonus);
	if (aggregate.geo_bonus != 0)
		printf("Geo DMG Bonus - %g%%\n", aggregate.geo_bonus);
	if (aggregate.physical_bonus != 0)
		printf("Physical DMG Bonus - %g%%\n", aggregate.physical_bonus);

	for (int i = 0; i < 5; i++) {
		printf("\n");
		artifact_print(in.artifacts[i]);
	}
}
