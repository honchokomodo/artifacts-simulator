// AUTOGEN CharacterType AMBER
// AUTOGEN character2str Amber
// TODO: get actual pics
// AUTOGEN character2icon "resources/images/characters/character_nothing_icon.png"
// AUTOGEN character2portrait "resources/images/characters/character_nothing_portrait.png"
// woah! a comment that isn't processed by the codegen!

// AUTOGEN character2talent amber_talent_func
void amber_talent_func(CharacterTalentArgs in)
{
	// does nothing for now
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
		.stats.ar[ATK_PERCENT] = bonusatk[ascension],
	};

	return character_base_stats(out, 4, in.level, ascension, base_hp,
			base_atk, base_def, asc_hp, asc_atk, asc_def);
}
// AUTOGEN end

// AUTOGEN character2ui amber_ui_func
void amber_ui_func(CharacterUIArgs args)
{
	// does nothing for now
}
// AUTOGEN end

// trailing?
