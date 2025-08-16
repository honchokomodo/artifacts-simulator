// AUTOGEN ArtifactSet MARECHAUSSEE_HUNTER
// AUTOGEN set2str Marechaussee Hunter

// AUTOGEN set2bonus noop_set_bonus_func
void marechaussee_hunter_bonus_func(SetBonusArgs in)
{
	if (in.num_pieces < 2) return;
	in.accumulators->all_bonus += 15.0;

	if (in.num_pieces < 4) return;
	in.accumulators->ar[CRIT_RATE] += 12.0 * in.loadout->bonus2;
}
// AUTOGEN end

// AUTOGEN set2ui marechaussee_hunter_ui_func
void marechaussee_hunter_ui_func(ArtifactLoadout * in)
{
	// does nothing for now
}
// AUTOGEN end
