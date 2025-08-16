// AUTOGEN WeaponType SKYWARD_HARP
// AUTOGEN weapon2str Skyward Harp
// AUTOGEN weapon2icon "resources/images/weapons/weapon_nothing_icon.png"
// AUTOGEN weapon2icon_asc "resources/images/weapons/weapon_nothing_asc_icon.png"

// AUTOGEN weapon2passive skyward_harp_passive_func
void skyward_harp_passive_func(WeaponPassiveArgs in)
{
	/* from wiki:
	   Echoing Ballad Increases CRIT DMG by 20%. Hits have a 60% chance to
	   inflict a small AoE attack, dealing 125% Physical ATK DMG. Can only
	   occur once every 4s.
	   */

	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

// AUTOGEN weapon2generator skyward_harp_generator_func
Weapon skyward_harp_generator_func(Weapon in)
{
	int ascension = weapon_check_ascension(in.level, in.ascension);

	static int const table[] = {
		// values obtained from wiki
		// https://genshin-impact.fandom.com/wiki/Skyward_Harp
		// ascension 0: lv 1-20
		48, 133,
		// ascension 1: lv 20-40
		164, 261,
		// ascension 2: lv 40-50
		292, 341,
		// ascension 3: lv 50-60
		373, 423,
		// ascension 4: lv 60-70
		455, 506,
		// ascension 5: lv 70-80
		537, 590,
		// ascension 6: lv 80-90
		621, 674,
	};

	float base_atk = weapon_base_atk(in.level, ascension, table);

	// from wiki: CRIT RATE += 4.8% at level 1
	float bonus_value = 4.8 * weapon_bonus_factor(in.level);

	Weapon out = {
		.type = SKYWARD_HARP,
		.level = in.level,
		.ascension = ascension,
		.refinement = in.refinement,

		.atk = base_atk,
		.bonus = {CRIT_RATE, bonus_value},
	};

	return out;
}
// AUTOGEN end

// AUTOGEN weapon2ui skyward_harp_ui_func
void skyward_harp_ui_func(Weapon * in)
{
	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

