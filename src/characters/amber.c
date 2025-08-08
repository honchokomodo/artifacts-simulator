// AUTOGEN CharacterType AMBER
// AUTOGEN character2str Amber
// woah! a comment that isn't processed by the codegen!

// AUTOGEN character2talent amber_talent_func
void amber_talent_func(CharacterTalentArgs in)
{
	// do nothing for now
}
// AUTOGEN end

// AUTOGEN character2generator amber_generator_func
CharacterStats amber_generator_func(CharacterStats in)
{
	CharacterStats amber90 = {
		.name = "Amber",
		.level = 90,
		.constellation = 6,

		// values obtained from wiki
		.hp = 9461.18,
		.atk = 223.02,
		.atk_percent = 24.0,
		.def = 600.62,
		.crit_rate = 5.0,
		.crit_damage = 50.0,
		.energy_recharge = 100.0,
	};
	
	return amber90;
}
// AUTOGEN end

// AUTOGEN character2ui amber_ui_func
void amber_ui_func(CharacterStats * in)
{
	char * c2title = "Bunny Triggered";
	char * c2desc = "Baron Bunny, new and improved! Hitting Baron Bunny's foot with a fully-charged Aimed Shot manually detonates it.\n"
"Explosion via manual detonation deals 200% additional DMG.";
	toggle_switch_text(&in->c2data, c2title, c2desc);
}
// AUTOGEN end

// trailing?
