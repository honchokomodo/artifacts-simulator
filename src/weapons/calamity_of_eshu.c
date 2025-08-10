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
	//TODO: un-hardcode this
	Weapon calamity_of_eshu_r5_90 = {
		.type = CALAMITY_OF_ESHU,
		.name = "Calamity of Eshu",
		.refinement = 5,
		.level = 90,
		.atk = 565,
		.bonus = {ATK_PERCENT, 27.6},
	};

	return calamity_of_eshu_r5_90;
}
// AUTOGEN end

// AUTOGEN weapon2ui calamity_of_eshu_ui_func
void calamity_of_eshu_ui_func(Weapon * in)
{
	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

