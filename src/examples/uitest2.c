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
	.width = {1, 1, 1, 1},
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
		.character = CHARACTER_NEW(AMBER,
				.level = 90,
				.constellation = 6,
				.talent = {10, 10, 10}),
		.weapon = WEAPON_NEW(SKYWARD_HARP,
				.level = 90,
				.refinement = 1),
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

