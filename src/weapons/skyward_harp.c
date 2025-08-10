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
	//TODO: un-hardcode this
	Weapon skyward_harp_r1_90 = {
		.type = SKYWARD_HARP,
		.name = "Skyward Harp",
		.refinement = 1,
		.level = 90,
		.atk = 674,
		.bonus = {CRIT_RATE, 22.1},
	};

	return skyward_harp_r1_90;
}
// AUTOGEN end

// AUTOGEN weapon2ui skyward_harp_ui_func
void skyward_harp_ui_func(Weapon * in)
{
	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

