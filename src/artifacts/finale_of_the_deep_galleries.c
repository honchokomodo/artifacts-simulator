// AUTOGEN ArtifactSet FINALE_OF_THE_DEEP_GALLERIES
// AUTOGEN set2str Finale of the Deep Galleries
// TODO: get actual pics
// AUTOGEN flowerpath "resources/images/artifacts/set_nothing/dereference.png"
// AUTOGEN featherpath "resources/images/artifacts/set_nothing/arrow.png"
// AUTOGEN sandspath "resources/images/artifacts/set_nothing/alarm_clock.png"
// AUTOGEN gobletpath "resources/images/artifacts/set_nothing/mug.png"
// AUTOGEN circletpath "resources/images/artifacts/set_nothing/earbuds.png"

// AUTOGEN set2bonus finale_of_the_deep_galleries_bonus_func
void finale_of_the_deep_galleries_bonus_func(SetBonusArgs in)
{
	if (in.num_pieces < 2) return;
	in.accumulators->ar[CRYO_BONUS] += 15.0;

	// TODO: handle whether the player is using their burst or normal
	if (in.num_pieces < 4) return;
	in.accumulators->all_bonus += 60.0;
}
// AUTOGEN end

// AUTOGEN set2ui finale_of_the_deep_galleries_ui_func
void finale_of_the_deep_galleries_ui_func(ArtifactLoadout * in)
{
	// does nothing for now
}
// AUTOGEN end
