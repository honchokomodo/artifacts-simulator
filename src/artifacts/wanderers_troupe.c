#ifdef TEMPLATE_ArtifactSet
	WANDERERS_TROUPE,
#endif

#ifdef TEMPLATE_set2str
	[WANDERERS_TROUPE] = "Wanderer's Troupe",
#endif

// TODO: get actual pics
#ifdef TEMPLATE_flowerpath
	[WANDERERS_TROUPE] = "resources/images/artifacts/set_nothing/dereference.png",
#endif

#ifdef TEMPLATE_featherpath
	[WANDERERS_TROUPE] = "resources/images/artifacts/set_nothing/arrow.png",
#endif

#ifdef TEMPLATE_sandspath
	[WANDERERS_TROUPE] = "resources/images/artifacts/set_nothing/alarm_clock.png",
#endif

#ifdef TEMPLATE_gobletpath
	[WANDERERS_TROUPE] = "resources/images/artifacts/set_nothing/mug.png",
#endif

#ifdef TEMPLATE_circletpath
	[WANDERERS_TROUPE] = "resources/images/artifacts/set_nothing/earbuds.png",
#endif

#ifdef TEMPLATE_set2bonus_impl
BuffElement wanderers_troupe_bonus_func(SetBonusArgs in)
{
	BuffElement out = {0};

	if (in.num_pieces < 2) return out;
	out.label = "Wanderer's Troupe 2-Piece Bonus";
	out.buff.ar[ELEMENTAL_MASTERY] += 80;

	return out;

	/* 4pc bonus is optional so it is handled by set2ui
	if (in.num_pieces < 4) return;
	if (in.loadout->bonus2)
		in.accumulators->all_bonus += 35.0;
		*/
}
#endif

#ifdef TEMPLATE_set2bonus_arr
	[WANDERERS_TROUPE] = wanderers_troupe_bonus_func,
#endif

#ifdef TEMPLATE_set2ui_impl
void wanderers_troupe_ui_func(ArtifactLoadout * in)
{
	// does nothing for now
}
#endif

#ifdef TEMPLATE_set2ui_arr
	[WANDERERS_TROUPE] = wanderers_troupe_ui_func,
#endif
