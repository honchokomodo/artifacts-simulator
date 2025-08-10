// AUTOGEN WeaponType THUNDERING_PULSE
// AUTOGEN weapon2str Thundering Pulse
// AUTOGEN weapon2icon "resources/images/weapons/weapon_nothing_icon.png"
// AUTOGEN weapon2icon_asc "resources/images/weapons/weapon_nothing_asc_icon.png"

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
	// TODO: un-hardcode this
	Weapon thundering_pulse_r1_90 = {
		.type = THUNDERING_PULSE,
		.name = "Thundering Pulse",
		.refinement = 1,
		.level = 90,
		.atk = 608,
		.bonus = {CRIT_DAMAGE, 66.2},
	};

	return thundering_pulse_r1_90;
}
// AUTOGEN end

// AUTOGEN weapon2ui thundering_pulse_ui_func
void thundering_pulse_ui_func(Weapon * in)
{
	// do nothing for now
	// TODO: implement this
}
// AUTOGEN end

