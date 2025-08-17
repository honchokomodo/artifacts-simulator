// AUTOGEN WeaponType THUNDERING_PULSE
// AUTOGEN weapon2str Thundering Pulse
// AUTOGEN weapon2icon "resources/images/weapons/thundering_pulse_icon.png"
// TODO: get the ascended version of the weapon icon
// AUTOGEN weapon2icon_asc "resources/images/weapons/thundering_pulse_icon.png"

// AUTOGEN weapon2passive thundering_pulse_passive_func
void thundering_pulse_passive_func(WeaponPassiveArgs in)
{
	/* from wiki:
	   Rule By Thunder Increases ATK by 20~40% and grants the might of the
	   Thunder Emblem.  At stack levels 1/2/3, the Thunder Emblem increases
	   Normal Attack DMG by 12/24/40~24/48/80%. The character will obtain 1
	   stack of Thunder Emblem in each of the following scenarios: Normal
	   Attack deals DMG (stack lasts 5s), casting Elemental Skill (stack
	   lasts 10s); Energy is less than 100% (stack disappears when Energy
	   is full). Each stack's duration is calculated independently.
	   */

	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

// AUTOGEN weapon2generator thundering_pulse_generator_func
Weapon thundering_pulse_generator_func(Weapon in)
{
	int ascension = check_ascension(in.level, in.ascension);

	static int const table[] = {
		// values obtained from wiki
		// https://genshin-impact.fandom.com/wiki/Thundering_Pulse
		// ascension 0: lv 1-20
		46, 122,
		// ascension 1: lv 20-40
		153, 235,
		// ascension 2: lv 40-50
		266, 308,
		// ascension 3: lv 50-60
		340, 382,
		// ascension 4: lv 60-70
		414, 457,
		// ascension 5: lv 70-80
		488, 552,
		// ascension 6: lv 80-90
		563, 608,
	};

	float base_atk = weapon_base_atk(in.level, ascension, table);

	// from wiki: CRIT DMG += 14.4% at level 1
	float bonus_value = 14.4 * weapon_bonus_factor(in.level);

	Weapon out = {
		.type = THUNDERING_PULSE,
		.level = in.level,
		.ascension = ascension,
		.refinement = in.refinement,

		.atk = base_atk,
		.bonus = {CRIT_DAMAGE, bonus_value},
	};

	return out;
}
// AUTOGEN end

// AUTOGEN weapon2ui thundering_pulse_ui_func
void thundering_pulse_ui_func(Weapon * in)
{
	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

