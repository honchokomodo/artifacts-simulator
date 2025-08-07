// AUTOGEN CharacterType SKIRK
// AUTOGEN character2str Skirk

// AUTOGEN character2talent skirk_talent_func
void skirk_talent_func(CharacterTalentArgs in)
{
	// do nothing for now
}
// AUTOGEN end

// AUTOGEN character2generator skirk_generator_func
CharacterStats skirk_generator_func(CharacterStats in)
{
	CharacterStats skirk90 = {
		.name = "Skirk",
		.level = 90,

		// values obtained from wiki
		.hp = 12417.35,
		.atk = 358.77,
		.def = 806.21,
		.crit_rate = 5.0,
		.crit_damage = 50.0 + 38.4,
		.energy_recharge = 100.0,
	};
	return skirk90;
}
// AUTOGEN end




