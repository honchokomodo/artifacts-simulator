#include <stdio.h>
#include <stdlib.h>

#include "../components.c"
#include "../scenario.c"
#include "../artifact_ui.c"
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
Clay_BorderElementConfig icon_border_select = {
	.color = {0xFF, 0xFF, 0xFF, 0xFF},
	.width = {1, 1, 1, 2},
};

void display_icons(la_Arena * arena)
{	
	CLAY({
		.layout = {
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
		}
	}){
		Texture2D * tex = ic_get_tex("resources/images/artifacts/icons/flower.png");
		CLAY({
			.layout = {
				//.sizing.width = CLAY_SIZING_PERCENT(0.2),
				.sizing.height = CLAY_SIZING_FIXED(75),
			},
			.border = icon_border_select,
			.image.imageData = tex,
			.aspectRatio = tex->width / (float) tex->height,
		}) {}
	}
}

void display_artifact_set(la_Arena * arena, Scenario * scenario)
{
	CLAY({
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.padding = global_padding,
		},
		.border = easy_border,
	}) {
		display_icons(arena);

		Texture2D * tex = ic_get_tex(artifact_get_image(scenario->loadout.flower.set, scenario->loadout.flower.piece));
		CLAY({
			.layout = {
				.sizing.width = CLAY_SIZING_FIXED(tex->width),
			},
			.border = easy_border,
			.image.imageData = tex,
			.aspectRatio = tex->width / (float) tex->height,
		}) {}

		CLAY({
			.border = easy_border,
			.layout = {
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing = layoutExpand,
			},
		}) {
			text_large(ch2str("ahhhhhhhh"));
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
	Clay_Raylib_Initialize(1024, 768, "artifact ui test", WINDOW_CONFIG_FLAGS);
	SetTargetFPS(60);

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
        };
	scenario.accumulators = aggregate_stats(scenario, scenario.active_set_bonuses);

	UI_Data uiData = {
		.scenario = &scenario,
	};

	Clay_SetDebugModeEnabled(true);

	while(!WindowShouldClose()) {
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
				.padding = global_padding,
				.childGap = global_gap,
				.sizing = layoutExpand,
			},
			.clip = {
				.vertical = true,
				.childOffset = Clay_GetScrollOffset(),
			},
		}) {
			display_artifact_set(&arena, &scenario);
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
