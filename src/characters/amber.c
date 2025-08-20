// AUTOGEN CharacterType AMBER
// AUTOGEN character2str Amber
// TODO: get actual pics
// AUTOGEN character2icon "resources/images/characters/character_nothing_icon.png"
// AUTOGEN character2portrait "resources/images/characters/character_nothing_portrait.png"
// woah! a comment that isn't processed by the codegen!

// AUTOGEN character2talent amber_talent_func
void amber_talent_func(CharacterTalentArgs in)
{
	if (in.character.a4data) {
		in.accumulators->ar[ATK_PERCENT] += 15.0;
	}

	if (in.character.c2data) {
		in.accumulators->all_bonus += 200.0;
	}

	if (in.character.c6data) {
		in.accumulators->ar[ATK_PERCENT] += 15.0;
	}
}
// AUTOGEN end

// AUTOGEN character2generator amber_generator_func
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
		.atk_percent = bonusatk[ascension],
	};

	return character_base_stats(out, 4, in.level, ascension, base_hp,
			base_atk, base_def, asc_hp, asc_atk, asc_def);
}
// AUTOGEN end

// AUTOGEN character2ui amber_ui_func
void amber_ui_func(CharacterUIArgs args)
{
	/*
	char * a4title = "Ascension 4: Every Arrow Finds Its Target";
	char * a4desc = "Aimed Shot hits on weak spots increase ATK by 15% for"
		"10s.";
	if (in->ascension >= 4) {
		toggle_switch_text(&in->a4data, a4title, a4desc, NULL);
	}

	char * c2title = "Constellation 2: Bunny Triggered";
	char * c2desc = "Baron Bunny, new and improved! Hitting Baron Bunny's"
		"foot with a fully-charged Aimed Shot manually detonates it.\n"
		"Explosion via manual detonation deals 200% additional DMG.";
	if (in->constellation >= 2) {
		toggle_switch_text(&in->c2data, c2title, c2desc, NULL);
	}

	char * c6title = "Constellation 6: Wildfire";
	char * c6desc = "Fiery Rain increases all party members' Movement SPD"
		"by 15% and ATK by 15% for 10s.";
	if (in->constellation >= 6) {
		toggle_switch_text(&in->c6data, c6title, c6desc, NULL);
	}
	*/
}
// AUTOGEN end

// trailing?
