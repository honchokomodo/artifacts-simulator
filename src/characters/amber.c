// AUTOGEN CharacterType AMBER
// AUTOGEN character2str Amber
// TODO: get actual pics
// AUTOGEN character2icon "resources/images/characters/character_nothing_icon.png"
// AUTOGEN character2portrait "resources/images/characters/character_nothing_portrait.png"
// woah! a comment that isn't processed by the codegen!

// AUTOGEN character2talent amber_talent_func
void amber_talent_func(CharacterTalentArgs in)
{
	// do nothing for now
	// TODO: fill this out
}
// AUTOGEN end

// AUTOGEN character2generator amber_generator_func
CharacterStats amber_generator_func(CharacterStats in)
{
	/* important variables:
	 * in.level
	 */

	int ascension = character_check_ascension(in.level, in.ascension);

	float base_hp = 793.2582;
	float base_atk = 18.6984;
	float base_def = 50.358;

	float lvlfac = character_level_multiplier(4, in.level);

	float asc_hp = 2838.2634;
	float asc_atk = 66.90411;
	float asc_def = 180.18;

	float ascfac = character_ascension_multiplier(ascension);

	static float const bonusatk[] = {
		[2] = 6.0,
		[3] = 12.0,
		[4] = 12.0,
		[5] = 18.0,
		[6] = 24.0,
	};

	CharacterStats out = {
		.type = in.type,
		.level = in.level,
		.constellation = in.constellation,
		.talent = in.talent,
		.name = "Amber",

		.hp = base_hp * lvlfac + asc_hp * ascfac,
		.atk = base_atk * lvlfac + asc_atk * ascfac,
		.def = base_def * lvlfac + asc_def * ascfac,

		.crit_rate = 5.0,
		.crit_damage = 50.0,
		.energy_recharge = 100.0,
		.atk_percent = bonusatk[ascension],
	};

	/*
	CharacterStats amber90 = {
		.name = "Amber",
		.level = 90,
		.constellation = 6,

		// values obtained from wiki
		.hp = 9461.18,
		.atk = 223.02,
		.atk_percent = 24.0,
		.def = 600.62,
		.crit_rate = 5.0,
		.crit_damage = 50.0,
		.energy_recharge = 100.0,
	};
	*/
	
	return out;
}
// AUTOGEN end

// AUTOGEN character2ui amber_ui_func
void amber_ui_func(CharacterStats * in)
{
	char * a4title = "Ascension 4: Every Arrow Finds Its Target";
	char * a4desc = "Aimed Shot hits on weak spots increase ATK by 15% for 10 s.";
	toggle_switch_text(&in->a4data, a4title, a4desc);

	char * c2title = "Constellation 2: Bunny Triggered";
	char * c2desc = "Baron Bunny, new and improved! Hitting Baron Bunny's foot with a fully-charged Aimed Shot manually detonates it.\n"
		"Explosion via manual detonation deals 200% additional DMG.";
	toggle_switch_text(&in->c2data, c2title, c2desc);

	char * c6title = "Constellation 6: Wildfire";
	char * c6desc = "Fiery Rain increases all party members' Movement SPD by 15% and ATK by 15% for 10s.";
	toggle_switch_text(&in->c6data, c6title, c6desc);
}
// AUTOGEN end

// trailing?
