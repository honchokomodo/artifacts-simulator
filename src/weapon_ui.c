#ifndef WEAPON_UI_C
#define WEAPON_UI_C

#include "weapon.c"
#include "components.c"

typedef void (*WeaponUIFunc)(Weapon *);
void noop_weapon_ui_func(Weapon * in)
{
	// this function does nothing
}

#define TEMPLATE_weapon2ui_impl
#include "weapons/weapons_list.h"
#undef TEMPLATE_weapon2ui_impl

WeaponUIFunc const weapon2ui[] = {
	[WEAPON_NOTHING] = noop_weapon_ui_func,
#define TEMPLATE_weapon2ui_arr
#include "weapons/weapons_list.h"
#undef TEMPLATE_weapon2ui_arr
};

#endif
