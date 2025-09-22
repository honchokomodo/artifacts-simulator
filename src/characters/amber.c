#ifdef TEMPLATE_CharacterType
	AMBER,
#endif

#ifdef TEMPLATE_character2str
	[AMBER] = "Amber",
#endif

// TODO: get actual pics
#ifdef TEMPLATE_character2icon
	[AMBER] = "resources/images/characters/character_nothing_icon.png",
#endif

#ifdef TEMPLATE_character2portrait
	[AMBER] = "resources/images/characters/character_nothing_portrait.png",
#endif

#ifdef TEMPLATE_character2talent_impl
float amber_fully_charged_shot(CharacterAttackArgs in)
{
	static float const scaling[] = {
		// values obtained from wiki
		// https://genshin-impact.fandom.com/wiki/Amber
		[1] = 124,
		[2] = 133.3,
		[3] = 142.6,
		[4] = 155,
		[5] = 164.3,
		[6] = 173.6,
		[7] = 186,
		[8] = 198.4,
		[9] = 210.8,
		[10] = 223.2,
		[11] = 235.6,
	};

	float scale_fac = scaling[in.character.talent.normal] / 100;

	float total_dmg_bonus = in.stats.ar[PYRO_BONUS] + in.stats.ar[BONUS_DAMAGE];
	float total_dmg_bonus_fac = 1 + total_dmg_bonus / 100;

	float enemy_def_fac = enemy_defense_fac(in.enemy, in.character.level);
	float enemy_res_fac = enemy_resistance_fac(in.enemy.pyro_res);

	// TODO: handle reaction bonuses like cwof 4p
	float reaction_mult = amplifying_multiplier(in.reaction, in.stats.ar[ELEMENTAL_MASTERY], 0);

	float total_atk = in.stats.ar[ATK_AGGREGATE];
	float damage = scale_fac * total_atk * total_dmg_bonus_fac * enemy_def_fac * enemy_res_fac * reaction_mult;

	float crit_fac = 1 + in.stats.ar[CRIT_DAMAGE] / 100;
	float mean_crit_fac = 1 + in.stats.ar[CRIT_DAMAGE] * in.stats.ar[CRIT_RATE] / 10000;

	if (in.crit == ON_CRIT) return damage * crit_fac;
	if (in.crit == OFF_CRIT) return damage;
	if (in.crit == MEAN_CRIT) return damage * mean_crit_fac;

	return 0; // should be unreachable
}

void amber_talent_func(CharacterTalentArgs in)
{
	// does nothing for now
}
#endif

#ifdef TEMPLATE_character2talent_arr
	[AMBER] = amber_talent_func,
#endif

#ifdef TEMPLATE_character2generator_impl
CharacterStats amber_generator_func(CharacterStats in)
{
	int ascension = check_ascension(in.level, in.ascension);

	// values obtained from wiki
	// https://genshin-impact.fandom.com/wiki/Character/Level_Scaling
	float base_hp = 793.2582;
	float base_atk = 18.6984;
	float base_def = 50.358;
	float asc_hp = 2838.2634;
	float asc_atk = 66.90411;
	float asc_def = 180.18;

	static float const bonusatk[] = {
		// values obtained from wiki
		// https://genshin-impact.fandom.com/wiki/Amber
		[2] = 6.0,
		[3] = 12.0,
		[4] = 12.0,
		[5] = 18.0,
		[6] = 24.0,
	};

	CharacterStats out = {
		.type = AMBER,
		.level = in.level,
		.ascension = ascension,
		.constellation = in.constellation,
		.talent = in.talent,
		.stats.ar[ATK_PERCENT] = bonusatk[ascension],
	};

	return character_base_stats(out, 4, in.level, ascension, base_hp,
			base_atk, base_def, asc_hp, asc_atk, asc_def);
}
#endif

#ifdef TEMPLATE_character2generator_arr
	[AMBER] = amber_generator_func,
#endif

#ifdef TEMPLATE_character2ui_impl
void amber_ui_func(CharacterUIArgs args)
{
	// does nothing for now
}
#endif

#ifdef TEMPLATE_character2ui_arr
	[AMBER] = amber_ui_func,
#endif
