// AUTOGEN CharacterType SKIRK
// AUTOGEN character2str Skirk
// TODO: get actual pics
// AUTOGEN character2icon "resources/images/characters/character_nothing_icon.png"
// AUTOGEN character2portrait "resources/images/characters/character_nothing_portrait.png"

// AUTOGEN character2talent skirk_talent_func
void skirk_talent_func(CharacterTalentArgs in)
{
	// do nothing for now
	// TODO: fill this out
}
// AUTOGEN end

// AUTOGEN character2generator skirk_generator_func
CharacterStats skirk_generator_func(CharacterStats in)
{
	int ascension = character_check_ascension(in.level, in.ascension);

	// values obtained from wiki
	// https://genshin-impact.fandom.com/wiki/Character/Level_Scaling
	float base_hp = 966.6665;
	float base_atk = 27.93;
	float base_def = 62.76167;
	float asc_hp = 3969.6553;
	float asc_atk = 114.6873;
	float asc_def = 257.7393;

	static float const bonuscd[] = {
		// values obtained from wiki
		// https://genshin-impact.fandom.com/wiki/Skirk
		[2] = 9.6,
		[3] = 19.2,
		[4] = 19.2,
		[5] = 28.8,
		[6] = 38.4,
	};

	CharacterStats out = {
		.type = SKIRK,
		.level = in.level,
		.ascension = ascension,
		.constellation = in.constellation,
		.talent = in.talent,
		.name = "Skirk",
	};

	out = character_base_stats(out, 5, in.level, ascension, base_hp, base_atk, base_def, asc_hp, asc_atk, asc_def);

	out.crit_damage += bonuscd[ascension];
	return out;
}
// AUTOGEN end

// AUTOGEN character2ui skirk_ui_func
void skirk_ui_func(CharacterStats * in)
{
	// TODO: implement this
}
// AUTOGEN end
