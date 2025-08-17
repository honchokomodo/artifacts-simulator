// AUTOGEN WeaponType CALAMITY_OF_ESHU
// AUTOGEN weapon2str Calamity of Eshu
// AUTOGEN weapon2icon "resources/images/weapons/weapon_nothing_icon.png"
// AUTOGEN weapon2icon_asc "resources/images/weapons/weapon_nothing_asc_icon.png"

// AUTOGEN weapon2passive calamity_of_eshu_passive_func
void calamity_of_eshu_passive_func(WeaponPassiveArgs in)
{
	/* from wiki:
	   Diffusing Boundary While characters are protected by a Shield, DMG
	   dealt by Normal and Charged Attacks is increased by 40%, and Normal
	   and Charged Attack CRIT Rate is increased by 16%.
	   */

	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

// AUTOGEN weapon2generator calamity_of_eshu_generator_func
Weapon calamity_of_eshu_generator_func(Weapon in)
{
	int ascension = check_ascension(in.level, in.ascension);

	static int const table[] = {
		// values obtained from wiki
		// https://genshin-impact.fandom.com/wiki/Calamity_of_Eshu
		// ascension 0: lv 1-20
		44, 119,
		// ascension 1: lv 20-40
		144, 226,
		// ascension 2: lv 40-50
		252, 293,
		// ascension 3: lv 50-60
		319, 361,
		// ascension 4: lv 60-70
		387, 429,
		// ascension 5: lv 70-80
		455, 497,
		// ascension 6: lv 80-90
		523, 565,
	};

	float base_atk = weapon_base_atk(in.level, ascension, table);

	// from wiki: ATK% += 6% at level 1
	float bonus_value = 6.0 * weapon_bonus_factor(in.level);

	Weapon out = {
		.type = CALAMITY_OF_ESHU,
		.level = in.level,
		.ascension = ascension,
		.refinement = in.refinement,

		.atk = base_atk,
		.bonus = {ATK_PERCENT, bonus_value},
	};

	return out;
}
// AUTOGEN end

// AUTOGEN weapon2ui calamity_of_eshu_ui_func
void calamity_of_eshu_ui_func(Weapon * in)
{
	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

