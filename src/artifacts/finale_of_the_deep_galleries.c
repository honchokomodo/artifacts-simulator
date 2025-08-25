#ifdef TEMPLATE_ArtifactSet
	FINALE_OF_THE_DEEP_GALLERIES,
#endif

#ifdef TEMPLATE_set2str
	[FINALE_OF_THE_DEEP_GALLERIES] = "Finale of the Deep Galleries",
#endif

// TODO: get actual pics
#ifdef TEMPLATE_flowerpath
	[FINALE_OF_THE_DEEP_GALLERIES] = "resources/images/artifacts/set_nothing/dereference.png",
#endif

#ifdef TEMPLATE_featherpath
	[FINALE_OF_THE_DEEP_GALLERIES] = "resources/images/artifacts/set_nothing/arrow.png",
#endif

#ifdef TEMPLATE_sandspath
	[FINALE_OF_THE_DEEP_GALLERIES] = "resources/images/artifacts/set_nothing/alarm_clock.png",
#endif

#ifdef TEMPLATE_gobletpath
	[FINALE_OF_THE_DEEP_GALLERIES] = "resources/images/artifacts/set_nothing/mug.png",
#endif

#ifdef TEMPLATE_circletpath
	[FINALE_OF_THE_DEEP_GALLERIES] = "resources/images/artifacts/set_nothing/earbuds.png",
#endif

#ifdef TEMPLATE_set2bonus_impl
BuffElement finale_of_the_deep_galleries_bonus_func(SetBonusArgs in)
{
	BuffElement out = {0};

	if (in.num_pieces < 2) return out;
	out.label = "Finale of the Deep Galleries 2-Piece Bonus";
	out.buff.ar[CRYO_BONUS] += 15.0;

	return out;

	// 4pc bonus is optional, so it is handled by set2ui.
}
#endif

#ifdef TEMPLATE_set2bonus_arr
	[FINALE_OF_THE_DEEP_GALLERIES] = finale_of_the_deep_galleries_bonus_func,
#endif

#ifdef TEMPLATE_set2ui_impl
void finale_of_the_deep_galleries_ui_func(ArtifactLoadout * in)
{
	// does nothing for now
}
#endif

#ifdef TEMPLATE_set2ui_arr
	[FINALE_OF_THE_DEEP_GALLERIES] = finale_of_the_deep_galleries_ui_func,
#endif
