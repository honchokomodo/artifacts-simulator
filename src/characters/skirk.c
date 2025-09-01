#ifdef TEMPLATE_CharacterType
	SKIRK,
#endif

#ifdef TEMPLATE_character2str
	[SKIRK] = "Skirk",
#endif

// TODO: get actual pics
#ifdef TEMPLATE_character2icon
	[SKIRK] = "resources/images/characters/character_nothing_icon.png",
#endif

#ifdef TEMPLATE_character2portrait
	[SKIRK] = "resources/images/characters/character_nothing_portrait.png",
#endif

#ifdef TEMPLATE_character2talent_impl
void skirk_talent_func(CharacterTalentArgs in)
{
	// do nothing for now
	// TODO: fill this out
}
#endif

#ifdef TEMPLATE_character2talent_arr
	[SKIRK] = skirk_talent_func,
#endif

#ifdef TEMPLATE_character2generator_impl
CharacterStats skirk_generator_func(CharacterStats in)
{
	int ascension = check_ascension(in.level, in.ascension);

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
	};

	out = character_base_stats(out, 5, in.level, ascension, base_hp,
			base_atk, base_def, asc_hp, asc_atk, asc_def);

	out.stats.ar[CRIT_DAMAGE] += bonuscd[ascension];
	return out;
}
#endif

#ifdef TEMPLATE_character2generator_arr
	[SKIRK] = skirk_generator_func,
#endif

#ifdef TEMPLATE_character2ui_impl
void skirk_ui_func(CharacterUIArgs args)
{
	static int deaths_crossing_stacks = 0;

	CLAY({
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = layoutExpand,
			.padding = 2,
			.childGap = 2,
		},
		.border = {{0xff, 0xff, 0xff, 0xff}, {1, 1, 1, 1}},
	}) {
		text_p(ch2str("nothing here yet"));
	}
}
#endif

#ifdef TEMPLATE_character2ui_arr
	[SKIRK] = skirk_ui_func,
#endif
