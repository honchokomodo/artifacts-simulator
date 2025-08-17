// AUTOGEN WeaponType MISTSPLITTER_REFORGED
// AUTOGEN weapon2str Mistsplitter Reforged
// AUTOGEN weapon2icon "resources/images/weapons/weapon_nothing_icon.png"
// AUTOGEN weapon2icon_asc "resources/images/weapons/weapon_nothing_asc_icon.png"

// AUTOGEN weapon2passive mistsplitter_reforged_passive_func
void mistsplitter_reforged_passive_func(WeaponPassiveArgs in)
{
	/* from wiki:
	   Mistsplitter's Edge Gain a 12~24% Elemental DMG Bonus for all
	   elements and receive the might of the Mistsplitter's Emblem. At
	   stack levels 1/2/3, Mistsplitter's Emblem provides a
	   8/16/28~16/32/56% Elemental DMG Bonus for the character's Elemental
	   Type.  The character will obtain 1 stack of Mistsplitter's Emblem in
	   each of the following scenarios: Normal Attack deals Elemental DMG
	   (stack lasts 5s), casting Elemental Burst (stack lasts 10s); Energy
	   is less than 100% (stack disappears when Energy is full). Each
	   stack's duration is calculated independently.
	   */

	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

// AUTOGEN weapon2generator mistsplitter_reforged_generator_func
Weapon mistsplitter_reforged_generator_func(Weapon in)
{
	int ascension = check_ascension(in.level, in.ascension);

	static int const table[] = {
		// values obtained from wiki
		// https://genshin-impact.fandom.com/wiki/Mistsplitter_Reforged
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

	// from wiki: CRIT DMG += 9.6% at level 1
	float bonus_value = 9.6 * weapon_bonus_factor(in.level);

	Weapon out = {
		.type = MISTSPLITTER_REFORGED,
		.level = in.level,
		.ascension = ascension,
		.refinement = in.refinement,

		.atk = base_atk,
		.bonus = {CRIT_DAMAGE, bonus_value},
	};

	return out;
}
// AUTOGEN end

// AUTOGEN weapon2ui mistsplitter_reforged_ui_func
void mistsplitter_reforged_ui_func(Weapon * in)
{
	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

