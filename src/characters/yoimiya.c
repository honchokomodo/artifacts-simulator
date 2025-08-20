// AUTOGEN CharacterType YOIMIYA
// AUTOGEN character2str Yoimiya
// TODO: possibly replace pics with smaller sizes because holy crap this one is enormous
// AUTOGEN character2portrait "resources/images/characters/yoimiya_portrait.png"

// AUTOGEN character2talent yoimiya_talent_func
void yoimiya_talent_func(CharacterTalentArgs in)
{
	// do nothing for now
}
// AUTOGEN end

// AUTOGEN character2generator yoimiya_generator_func
CharacterStats yoimiya_generator_func(CharacterStats in)
{
	int ascension = check_ascension(in.level, in.ascension);

	// values obtained from wiki
	// https://genshin-impact.fandom.com/wiki/Character/Level_Scaling
	float base_hp = 791.2556;
	float base_atk = 25.137;
	float base_def = 47.864;
	float asc_hp = 3249.3232;
	float asc_atk = 103.21857;
	float asc_def = 196.56;

	static float const bonuscr[] = {
		// values obtained from wiki
		// https://genshin-impact.fandom.com/wiki/Yoimiya
		[2] = 4.8,
		[3] = 9.6,
		[4] = 9.6,
		[5] = 14.4,
		[6] = 19.2,
	};

	CharacterStats out = {
		.type = YOIMIYA,
		.level = in.level,
		.ascension = ascension,
		.constellation = in.constellation,
		.talent = in.talent,
	};

	out = character_base_stats(out, 5, in.level, ascension, base_hp,
			base_atk, base_def, asc_hp, asc_atk, asc_def);

	out.crit_rate += bonuscr[ascension];
	return out;
}
// AUTOGEN end

// AUTOGEN character2ui yoimiya_ui_func
void yoimiya_ui_func(CharacterUIArgs args)
{
	// TODO: implement this
}
// AUTOGEN end

