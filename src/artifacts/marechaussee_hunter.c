// AUTOGEN set2bonus noop_set_bonus_func
// AUTOGEN end

// AUTOGEN set2ui marechaussee_hunter_ui_func
// AUTOGEN end

#ifdef TEMPLATE_ArtifactSet
	MARECHAUSSEE_HUNTER,
#endif

#ifdef TEMPLATE_set2str
	[MARECHAUSSEE_HUNTER] = "Marechaussee Hunter",
#endif

// TODO: get actual pics
#ifdef TEMPLATE_flowerpath
	[MARECHAUSSEE_HUNTER] = "resources/images/artifacts/set_nothing/dereference.png",
#endif

#ifdef TEMPLATE_featherpath
	[MARECHAUSSEE_HUNTER] = "resources/images/artifacts/set_nothing/arrow.png",
#endif

#ifdef TEMPLATE_sandspath
	[MARECHAUSSEE_HUNTER] = "resources/images/artifacts/set_nothing/alarm_clock.png",
#endif

#ifdef TEMPLATE_gobletpath
	[MARECHAUSSEE_HUNTER] = "resources/images/artifacts/set_nothing/mug.png",
#endif

#ifdef TEMPLATE_circletpath
	[MARECHAUSSEE_HUNTER] = "resources/images/artifacts/set_nothing/earbuds.png",
#endif

#ifdef TEMPLATE_set2bonus_impl
BuffElement marechaussee_hunter_bonus_func(SetBonusArgs in)
{
	BuffElement out = {0};

	if (in.num_pieces < 2) return out;
	out.label = "Marechaussee Hunter 2-Piece Bonus";
	out.buff.normal_bonus += 15.0;
	out.buff.charged_bonus += 15.0;

	return out;

	/* 4pc bonus is optional, so it will be handled by set2ui
	if (in.num_pieces < 4) return;
	in.accumulators->ar[CRIT_RATE] += 12.0 * in.loadout->bonus2;
	*/
}
#endif

#ifdef TEMPLATE_set2bonus_arr
	[MARECHAUSSEE_HUNTER] = marechaussee_hunter_bonus_func,
#endif

#ifdef TEMPLATE_set2ui_impl
void marechaussee_hunter_ui_func(ArtifactLoadout * in)
{
	// does nothing for now
}
#endif

#ifdef TEMPLATE_set2ui_arr
	[MARECHAUSSEE_HUNTER] = marechaussee_hunter_ui_func,
#endif
