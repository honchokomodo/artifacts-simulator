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

// trailing?
