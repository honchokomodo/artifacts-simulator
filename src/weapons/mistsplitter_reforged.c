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
	// TODO: un-hardcode this
	Weapon mistsplitter_reforged_r1_90 = {
		.type = MISTSPLITTER_REFORGED,
		.name = "Mistsplitter Reforged",
		.refinement = 1,
		.level = 90,
		.atk = 674,
		.bonus = {CRIT_DAMAGE, 44.1},
	};

	return mistsplitter_reforged_r1_90;
}
// AUTOGEN end

// AUTOGEN weapon2ui mistsplitter_reforged_ui_func
void mistsplitter_reforged_ui_func(Weapon * in)
{
	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

