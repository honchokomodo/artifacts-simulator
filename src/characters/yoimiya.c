// AUTOGEN CharacterType YOIMIYA
// AUTOGEN character2str Yoimiya
// TODO: possibly replace pics with smaller sizes because holy crap this one is enormous
// AUTOGEN character2portrait "resources/images/characters/yoimiya_portrait.png"

// AUTOGEN character2talent yoimiya_talent_func
void yoimiya_talent_func(CharacterTalentArgs in)
{
	// do nothing for now
}
// AUTOGEN end

// AUTOGEN character2generator yoimiya_generator_func
CharacterStats yoimiya_generator_func(CharacterStats in)
{
	CharacterStats yoimiya90 = {
		.type = YOIMIYA,
		.level = 90,

		//values obtained from wiki
		.hp = 10164.11,
		.atk = 322.89,
		.def = 614.84,
		.crit_rate = 5.0 + 19.2,
		.crit_damage = 50.0,
		.energy_recharge = 100.0,
	};
	return yoimiya90;
}
// AUTOGEN end
