#include <stdio.h>
#include <stdlib.h>

#include "../components.c"
#include "../scenario.c"
#include "../../build/include/artifacts_ui.c"
#include "../../build/include/characters_ui.c"
#include "../../build/include/weapons_ui.c"

enum tab_index {
	TAB_BENCHMARK,
	TAB_EQUIPMENT,
	TAB_BUFFS,
	TAB_COUNT,
};

typedef struct ui_data {
	Scenario * scenario;
} UI_Data;

int global_gap = 12;
Clay_Padding global_padding = {16, 16, 16, 16};
Clay_BorderElementConfig easy_border = {
	.color = {0xFF, 0xFF, 0xFF, 0xFF},
	//.width = {1, 1, 1, 1},
};

Clay_ElementDeclaration hcontainer()
{
	Clay_ElementDeclaration out = {
		.layout = {
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.sizing.width = CLAY_SIZING_GROW(0),
		},
		.border = easy_border,
	};
	
	return out;
}

void display_character_attributes(la_Arena * arena, Scenario * scenario)
{
#define STAT_DISPLAY(str, fmt, val) \
	do { \
		CLAY(hcontainer()) { \
			text_p(ch2str(str)); \
			CLAY({.layout.sizing = layoutExpand}) {} \
			text_p(ch2str(la_strfmt(arena, fmt, val))); \
		} \
	} while (0)

#define COND_DISPLAY(str, fmt, val) \
	do { \
		if (val != 0) { \
			STAT_DISPLAY(str, fmt, val); \
		} \
	} while (0)

	CLAY({
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			//.childGap = global_gap,
			.padding = global_padding, 
		},
		.border = easy_border,
	}) {
		CharacterStats character = scenario->character;
		Texture2D * tex = ic_get_tex(character2portrait[character.type]);
		CLAY({
			.layout = {
				.sizing = {
					.width = CLAY_SIZING_FIXED(300),
					.height = CLAY_SIZING_FIXED(300),
				},
				.padding = global_padding,
				//.childGap = global_gap,
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
			},
			.image.imageData = tex,
			.aspectRatio = tex->width / (float) tex->height,
			.border = easy_border,
		}) {
			CLAY(hcontainer()) {
				text_large(ch2str(character2str[character.type]));
				CLAY({.layout.sizing = layoutExpand}) {}
				text_p(ch2str(la_strfmt(arena, "lv. %d/%d", character.level, ascension_max_level(character.ascension))));
			}

			CLAY({.layout.sizing = layoutExpand}) {}

			STAT_DISPLAY("Constellation", "%d", character.constellation);

			CLAY(hcontainer()) {
				text_p(ch2str("Talents"));
				CLAY({.layout.sizing = layoutExpand}) {}
				text_p(ch2str(la_strfmt(arena, "%d, %d, %d", character.talent.normal, character.talent.skill, character.talent.burst)));
			}
		}

		CLAY({
			.layout = {
				.sizing.width = CLAY_SIZING_GROW(0),
				.padding = global_padding,
				//.childGap = global_gap,
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
			},
			.border = easy_border,
		}) {

			StatAccumulators stats = scenario->accumulators;

			STAT_DISPLAY("HP", "%g", stats.hp);
			STAT_DISPLAY("ATK", "%g", stats.atk);
			STAT_DISPLAY("DEF", "%g", stats.def);
			COND_DISPLAY("Elemental Mastery", "%g", stats.ar[ELEMENTAL_MASTERY]);
			STAT_DISPLAY("Crit RATE", "%g%%", stats.ar[CRIT_RATE]);
			STAT_DISPLAY("Crit DMG", "%g%%", stats.ar[CRIT_DAMAGE]);
			COND_DISPLAY("Healing Bonus", "%g%%", stats.ar[HEALING_BONUS]);
			STAT_DISPLAY("Energy Recharge", "%g%%", stats.ar[ENERGY_RECHARGE]);
			COND_DISPLAY("Pyro DMG Bonus", "%g%%", stats.ar[PYRO_BONUS]);
			COND_DISPLAY("Hydro DMG Bonus", "%g%%", stats.ar[HYDRO_BONUS]);
			COND_DISPLAY("Dendro DMG Bonus", "%g%%", stats.ar[DENDRO_BONUS]);
			COND_DISPLAY("Electro DMG Bonus", "%g%%", stats.ar[ELECTRO_BONUS]);
			COND_DISPLAY("Anemo DMG Bonus", "%g%%", stats.ar[ANEMO_BONUS]);
			COND_DISPLAY("Cryo DMG Bonus", "%g%%", stats.ar[CRYO_BONUS]);
			COND_DISPLAY("Geo DMG Bonus", "%g%%", stats.ar[GEO_BONUS]);
			COND_DISPLAY("Physical DMG Bonus", "%g%%", stats.ar[PHYSICAL_BONUS]);

#undef COND_DISPLAY
#undef STAT_DISPLAY
		}
	}
}

void display_weapon_attributes(la_Arena * arena, Scenario * scenario)
{
	CLAY({
		.layout = {
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			//.childGap = global_gap,
			.padding = global_padding, 
		},
		.border = easy_border,
	}) {
		Weapon weapon = scenario->weapon;

		Texture2D * tex = ic_get_tex(weapon_icon(weapon));
		CLAY({
			.layout = {
				.sizing = {
					.width = CLAY_SIZING_FIXED(200),
					.height = CLAY_SIZING_FIXED(200),
				},
			},
			.image.imageData = tex,
			.aspectRatio = tex->width / (float) tex->height,
			.border = easy_border,
		}) {}

		CLAY({
			.layout = {
				.sizing.width = CLAY_SIZING_GROW(0),
				.padding = global_padding,
				//.childGap = global_gap,
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
			},
			.border = easy_border,
		}) {
			int min_spacer = 10;

			CLAY(hcontainer()) {
				text_large(ch2str(weapon2str[weapon.type]));
				CLAY({.layout.sizing.width = CLAY_SIZING_GROW(min_spacer)}) {}
				text_p(ch2str(la_strfmt(arena, "lv. %d/%d", weapon.level, ascension_max_level(weapon.ascension))));
			}

			CLAY(hcontainer()) {
				text_p(ch2str("Refinement"));
				CLAY({.layout.sizing.width = CLAY_SIZING_GROW(min_spacer)}) {}
				text_p(ch2str(la_strfmt(arena, "%d", weapon.refinement)));
			}

			CLAY(hcontainer()) {
				text_p(ch2str("Base ATK"));
				CLAY({.layout.sizing.width = CLAY_SIZING_GROW(min_spacer)}) {}
				text_p(ch2str(la_strfmt(arena, "%g", weapon.atk)));
			}

			CLAY(hcontainer()) {
				text_p(ch2str(stat2str[weapon.bonus.type]));
				CLAY({.layout.sizing.width = CLAY_SIZING_GROW(min_spacer)}) {}
				text_p(ch2str(la_strfmt(arena, "%g%s", weapon.bonus.value, stat2pct[weapon.bonus.type])));
			}
		}
	}
}

void display_artifact1(la_Arena * arena, Artifact * artifact)
{
	CLAY({
		.layout = {
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			//.childGap = global_gap,
			.padding = global_padding,
		},
		.border = easy_border,
	}) {
		Texture2D * tex = ic_get_tex(artifact_get_image(artifact->set, artifact->piece));
		CLAY({
			.layout = {
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing = {
					.width = CLAY_SIZING_FIXED(128),
					.height = CLAY_SIZING_FIXED(128),
				},
				.padding = global_padding,
			},
			.border = easy_border,
			.image.imageData = tex,
			.aspectRatio = tex->width / (float) tex->height,
		}) {
			text_large(ch2str(stat2str[artifact->mainstat.type]));
			text_p(ch2str(la_strfmt(arena, "%s%g", stat2pct[artifact->mainstat.type], artifact->mainstat.value)));
			CLAY({.layout.sizing.height = CLAY_SIZING_GROW(0)}) {}
			text_p(ch2str(la_strfmt(arena, "+%d", artifact->level)));
		}

		CLAY({
			.layout = {
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing.width = CLAY_SIZING_GROW(0),
				.padding = global_padding,
			},
			.border = easy_border,
		}) {
			int min_spacer = 10;
			for (int i = 0; i < artifact->num_substats; i++) {
				Affix substat = artifact->substat[i];
				CLAY(hcontainer()) {
					text_p(ch2str(stat2str[substat.type]));
					CLAY({.layout.sizing.width = CLAY_SIZING_GROW(min_spacer)}) {}
					text_p(ch2str(la_strfmt(arena, "%g%s", substat.value, stat2pct[substat.type])));
				}
			}
		}
	}
}

void display_artifact_set(la_Arena * arena, Scenario * scenario)
{
	void (*displayfunc)(la_Arena *, Artifact *) = display_artifact1;

	CLAY({
		.layout = {
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			//.childGap = global_gap,
			.padding = global_padding,
		},
		.border = easy_border,
	}) {
		displayfunc(arena, &scenario->loadout.flower);
		displayfunc(arena, &scenario->loadout.feather);
		displayfunc(arena, &scenario->loadout.sands);
		displayfunc(arena, &scenario->loadout.goblet);
		displayfunc(arena, &scenario->loadout.circlet);
	}
}

void display_buffs(la_Arena * arena, Scenario * scenario)
{
	CLAY({
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			//.childGap = global_gap,
			.padding = global_padding,
		},
		.border = easy_border,
	}) {
		if (scenario->buffs_len <= 0) {
			text_p(ch2str("There are no buffs to show."));
			continue;
		}

		int min_spacer = 10;
		for (int i = 0; i < scenario->buffs_len; i++)
		{
			CLAY({
				.layout = {
					.layoutDirection = CLAY_TOP_TO_BOTTOM,
					.childGap = global_gap,
					.padding = global_padding,
				},
				.border = easy_border,
			}) {
#define COND_DISPLAY(str, fmt, val) \
	do { \
		if (val != 0) { \
			CLAY(hcontainer()) { \
				text_p(ch2str(str)); \
				CLAY({.layout.sizing.width = CLAY_SIZING_GROW(min_spacer)}) {} \
				text_p(ch2str(la_strfmt(arena, fmt, val))); \
			} \
		} \
	} while (0)

				BuffElement buff = scenario->buffs[i];

				text_p(ch2str(buff.label));

				COND_DISPLAY("Base HP", "%g", buff.buff.hp_base);
				COND_DISPLAY("Base ATK", "%g", buff.buff.atk_base);
				COND_DISPLAY("Base DEF", "%g", buff.buff.def_base);
				COND_DISPLAY("HP", "%g", buff.buff.hp);
				COND_DISPLAY("ATK", "%g", buff.buff.atk);
				COND_DISPLAY("DEF", "%g", buff.buff.def);
				COND_DISPLAY("HP%", "%g%%", buff.buff.ar[HP_PERCENT]);
				COND_DISPLAY("ATK%", "%g%%", buff.buff.ar[ATK_PERCENT]);
				COND_DISPLAY("DEF%", "%g%%", buff.buff.ar[DEF_PERCENT]);
				COND_DISPLAY("Bonus DMG", "%g%%", buff.buff.all_bonus);
				COND_DISPLAY("Multiplicative Factor", "%g", buff.buff.factor);
				COND_DISPLAY("Elemental Mastery", "%g", buff.buff.ar[ELEMENTAL_MASTERY]);
				COND_DISPLAY("Crit RATE", "%g%%", buff.buff.ar[CRIT_RATE]);
				COND_DISPLAY("Crit DMG", "%g%%", buff.buff.ar[CRIT_DAMAGE]);
				COND_DISPLAY("Healing Bonus", "%g%%", buff.buff.ar[HEALING_BONUS]);
				COND_DISPLAY("Energy Recharge", "%g%%", buff.buff.ar[ENERGY_RECHARGE]);
				COND_DISPLAY("Pyro DMG Bonus", "%g%%", buff.buff.ar[PYRO_BONUS]);
				COND_DISPLAY("Hydro DMG Bonus", "%g%%", buff.buff.ar[HYDRO_BONUS]);
				COND_DISPLAY("Dendro DMG Bonus", "%g%%", buff.buff.ar[DENDRO_BONUS]);
				COND_DISPLAY("Electro DMG Bonus", "%g%%", buff.buff.ar[ELECTRO_BONUS]);
				COND_DISPLAY("Anemo DMG Bonus", "%g%%", buff.buff.ar[ANEMO_BONUS]);
				COND_DISPLAY("Cryo DMG Bonus", "%g%%", buff.buff.ar[CRYO_BONUS]);
				COND_DISPLAY("Geo DMG Bonus", "%g%%", buff.buff.ar[GEO_BONUS]);
				COND_DISPLAY("Physical DMG Bonus", "%g%%", buff.buff.ar[PHYSICAL_BONUS]);

#undef COND_DISPLAY
			}
		}
	}

}

void HandleClayErrors(Clay_ErrorData errorData)
{
	printf("%s", errorData.errorText.chars);
}

int main(void)
{
	uint32_t WINDOW_CONFIG_FLAGS = 0
		| FLAG_WINDOW_RESIZABLE
	;
	Clay_Raylib_Initialize(1024, 768, "ui test", WINDOW_CONFIG_FLAGS);
	SetTargetFPS(60);
	//EnableEventWaiting();

	uint64_t clayRequiredMemory = Clay_MinMemorySize();
	Clay_Arena clayMemory = {
		.memory = malloc(clayRequiredMemory),
		.capacity = clayRequiredMemory,
	};

	Clay_Dimensions windowSize = {
		.width = GetScreenWidth(),
		.height = GetScreenHeight(),
	};
	Clay_ErrorHandler errorHandler = {HandleClayErrors};
	Clay_Context * clayContext = Clay_Initialize(clayMemory, windowSize, errorHandler);

	Font font;
	font = LoadFontEx("resources/fonts/honchokomono-regular-normal.otf", 48, NULL, 0);
	SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
	Clay_SetMeasureTextFunction(Raylib_MeasureText, &font);  

	ic_initcache(7, 100);
	la_Arena arena = {
		.buf = malloc(16384),
		.bufsz = 16384,
	};

	Scenario scenario = {
		.character = CHARACTER_NEW(SKIRK,
				.level = 90,
				.constellation = 0,
				.talent = {6, 8, 7}),
		.weapon = WEAPON_NEW(CALAMITY_OF_ESHU,
				.level = 90,
				.refinement = 5),

		.loadout.flower = {
			.piece = FLOWER, 
			.set = FINALE_OF_THE_DEEP_GALLERIES,
			.level = 20, .num_substats = 4,
			.mainstat = {HP_FLAT, 4780},
			.substat[0] = {CRIT_RATE, 7.8},
			.substat[1] = {ELEMENTAL_MASTERY, 42},
			.substat[2] = {ATK_PERCENT, 8.2},
			.substat[3] = {DEF_FLAT, 39},
		},

		.loadout.feather = {
			.piece = FEATHER,
			.set = FINALE_OF_THE_DEEP_GALLERIES,
			.level = 20, .num_substats = 4,
			.mainstat = {ATK_FLAT, 311},
			.substat[0] = {CRIT_RATE, 7.0},
			.substat[1] = {DEF_PERCENT, 5.8},
			.substat[2] = {CRIT_DAMAGE, 18.7},
			.substat[3] = {HP_FLAT, 598},
		},

		.loadout.sands = {
			.piece = SANDS,
			.set = WANDERERS_TROUPE,
			.level = 20, .num_substats = 4,
			.mainstat = {ATK_PERCENT, 46.6},
			.substat[0] = {CRIT_DAMAGE, 20.2},
			.substat[1] = {HP_PERCENT, 19.2},
			.substat[2] = {ELEMENTAL_MASTERY, 23},
			.substat[3] = {DEF_PERCENT, 5.1},
		},

		.loadout.goblet = {
			.piece = GOBLET,
			.set = FINALE_OF_THE_DEEP_GALLERIES,
			.level = 20, .num_substats = 4,
			.mainstat = {CRYO_BONUS, 46.6},
			.substat[0] = {ELEMENTAL_MASTERY, 33},
			.substat[1] = {HP_PERCENT, 9.3},
			.substat[2] = {ENERGY_RECHARGE, 18.1},
			.substat[3] = {ATK_FLAT, 19},
		},

		.loadout.circlet = {
			.piece = CIRCLET,
			.set = FINALE_OF_THE_DEEP_GALLERIES,
			.level = 20, .num_substats = 4,
			.mainstat = {CRIT_DAMAGE, 62.2},
			.substat[0] = {CRIT_RATE, 9.7},
			.substat[1] = {HP_PERCENT, 9.3},
			.substat[2] = {ATK_PERCENT, 5.3},
			.substat[3] = {HP_FLAT, 478},
		},

		.buffs_len = 2,
		.buffs[0] = {
			.label = "test buff",
			.buff.ar[ATK_PERCENT] = 15,
		},

		.buffs[1] = {
			.label = "test buff 2",
			.buff.ar[CRIT_RATE] = 15,
		}
	};
	scenario.accumulators = aggregate_stats(scenario);

	UI_Data uiData = {
		.scenario = &scenario,
	};

	Clay_SetDebugModeEnabled(true);

	while (!WindowShouldClose()) {
		windowSize.width = GetScreenWidth();
		windowSize.height = GetScreenHeight();
		Clay_SetLayoutDimensions(windowSize);

		Vector2 mousepos = GetMousePosition();
		Clay_SetPointerState(
			(Clay_Vector2) {mousepos.x, mousepos.y},
			IsMouseButtonDown(MOUSE_BUTTON_LEFT));

		Vector2 scroll = GetMouseWheelMoveV();
		Clay_UpdateScrollContainers(
				true,
				(Clay_Vector2) {scroll.x, scroll.y},
				GetFrameTime());

		Clay_BeginLayout();

		CLAY({
			.backgroundColor = COLOR_BG,
			.layout = {
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing = layoutExpand,
				.padding = global_padding,
				.childGap = global_gap,
			},
			.clip = {
				.vertical = true,
				.childOffset = Clay_GetScrollOffset(),
			},
		}) {
			display_character_attributes(&arena, &scenario);
			display_weapon_attributes(&arena, &scenario);
			display_artifact_set(&arena, &scenario);
			display_buffs(&arena, &scenario);
		}

		Clay_RenderCommandArray renderCommands = Clay_EndLayout();

		BeginDrawing();
		ClearBackground(BLACK);

		Clay_Raylib_Render(renderCommands, &font);

		EndDrawing();
		la_reset(&arena);
	}

	ic_destroycache();
	free(arena.buf);

	UnloadFont(font);
	Clay_Raylib_Close();
	free(clayMemory.memory);
	return 0;
}

