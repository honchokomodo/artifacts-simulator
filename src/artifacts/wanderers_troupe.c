// AUTOGEN ArtifactSet WANDERERS_TROUPE
// AUTOGEN set2str Wanderer's Troupe
// TODO: get actual pics
// AUTOGEN flowerpath "resources/images/artifacts/set_nothing/dereference.png"
// AUTOGEN featherpath "resources/images/artifacts/set_nothing/arrow.png"
// AUTOGEN sandspath "resources/images/artifacts/set_nothing/alarm_clock.png"
// AUTOGEN gobletpath "resources/images/artifacts/set_nothing/mug.png"
// AUTOGEN circletpath "resources/images/artifacts/set_nothing/earbuds.png"

// AUTOGEN set2bonus wanderers_troupe_bonus_func
void wanderers_troupe_bonus_func(SetBonusArgs in)
{
	if (in.num_pieces < 2) return;
	in.accumulators->ar[ELEMENTAL_MASTERY] += 80;

	if (in.num_pieces < 4) return;
	if (in.loadout->bonus2)
		in.accumulators->all_bonus += 35.0;
}
// AUTOGEN end

// AUTOGEN set2ui wanderers_troupe_ui_func
void wanderers_troupe_ui_func(ArtifactLoadout * in)
{
	// does nothing for now
}
// AUTOGEN end
