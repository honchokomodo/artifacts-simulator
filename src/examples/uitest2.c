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
	int * currentTabIndex;
} UI_Data;

int global_gap = 12;

void vline(void)
{
	CLAY({
		.backgroundColor = COLOR_BG_ALT,
		.layout.sizing = {
			.width = CLAY_SIZING_FIXED(2),
			.height = CLAY_SIZING_GROW(0),
		},
	}) {}
}

void hline(void)
{
	CLAY({
		.backgroundColor = COLOR_BG_ALT,
		.layout.sizing = {
			.width = CLAY_SIZING_GROW(0),
			.height = CLAY_SIZING_FIXED(2),
		},
	}) {}
}

void left_side_bar(UI_Data uiData)
{
	CLAY({
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = {
				.width = CLAY_SIZING_FIXED(200),
				.height = CLAY_SIZING_GROW(0),
			},
			.childGap = global_gap,
		},
	}) {
		
		CLAY({
			.backgroundColor = interactable_color(),
			.layout = {
				.sizing = layoutWide,
				.padding = CLAY_PADDING_ALL(6),
			},
			.border = {
				.color = COLOR_BORDER,
				.width = {2 * (*uiData.currentTabIndex == TAB_BENCHMARK)},
			},
		}) {
			assign_button(uiData.currentTabIndex, TAB_BENCHMARK, NULL);
			text_large(ch2str("Benchmark"));
		}

		CLAY({
			.backgroundColor = interactable_color(),
			.layout = {
				.sizing = layoutWide,
				.padding = CLAY_PADDING_ALL(6),
			},
			.border = {
				.color = COLOR_BORDER,
				.width = {2 * (*uiData.currentTabIndex == TAB_EQUIPMENT)},
			},
		}) {
			assign_button(uiData.currentTabIndex, TAB_EQUIPMENT, NULL);
			text_large(ch2str("Equipment"));
		}

		CLAY({
			.backgroundColor = interactable_color(),
			.layout = {
				.sizing = layoutWide,
				.padding = CLAY_PADDING_ALL(6),
			},
			.border = {
				.color = COLOR_BORDER,
				.width = {2 * (*uiData.currentTabIndex == TAB_BUFFS)},
			},
		}) {
			assign_button(uiData.currentTabIndex, TAB_BUFFS, NULL);
			text_large(ch2str("Buffs"));
		}
	}
}

void right_side_bar(UI_Data uiData)
{
	CLAY({
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = {
				.width = CLAY_SIZING_FIXED(400),
				.height = CLAY_SIZING_GROW(0),
			},
			.childGap = global_gap,
		},
	}) {
		Texture2D * tex = ic_get_tex(character2portrait[uiData.scenario->character.type]);

		CLAY({
			.layout.sizing = layoutExpand,
			.image.imageData = tex,
			.aspectRatio = tex->width / (float) tex->height,
		}) {}

		text_large(ch2str(character2str[uiData.scenario->character.type]));
	}
}

void tab_benchmark(UI_Data uiData)
{
	// TODO
}

void tab_equipment(UI_Data uiData)
{
	CLAY({
		.layout = {
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.sizing = layoutWide,
			.childGap = global_gap,
		},
	}) {
		Weapon weapon = uiData.scenario->weapon;
		Texture2D * tex = ic_get_tex(weapon2icon[weapon.type]);
		CLAY({
			.layout.sizing = {
				.height = CLAY_SIZING_FIXED(300),
			},
			.image.imageData = tex,
			.aspectRatio = tex->width / (float) tex->height,
		}) {}

		vline();

		CLAY({
			.layout = {
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing = layoutExpand,
				.childGap = global_gap,
			},
		}) {
			text_large(ch2str(weapon2str[weapon.type]));
		}
	}

	hline();
	
	// TODO: draw artifacts
}

void tab_buffs(UI_Data uiData)
{
	// TODO
}

void main_content(UI_Data uiData)
{
	CLAY({
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = layoutExpand,
			.childGap = global_gap,
		},
	}) {
		switch (*uiData.currentTabIndex)
		{
			case TAB_BENCHMARK:
				tab_benchmark(uiData);
				break;
			case TAB_EQUIPMENT:
				tab_equipment(uiData);
				break;
			case TAB_BUFFS:
				tab_buffs(uiData);
				break;
			default:
				 // do nothing
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
	SetTargetFPS(30);

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
		.character = CHARACTER_NEW(YOIMIYA, 0),
		.weapon = WEAPON_NEW(THUNDERING_PULSE, 0),
	};
	int currentTabIndex = 0;

	UI_Data uiData = {
		.scenario = &scenario,
		.currentTabIndex = &currentTabIndex,
	};

	while (!WindowShouldClose()) {
		windowSize.width = GetScreenWidth();
		windowSize.height = GetScreenHeight();
		Clay_SetLayoutDimensions(windowSize);

		Vector2 mousepos = GetMousePosition();
		Clay_SetPointerState(
			(Clay_Vector2) {mousepos.x, mousepos.y},
			IsMouseButtonDown(MOUSE_BUTTON_LEFT)
		);

		Clay_BeginLayout();

		CLAY({
			.backgroundColor = COLOR_BG,
			.layout = {
				.layoutDirection = CLAY_LEFT_TO_RIGHT,
				.sizing = layoutExpand,
				.padding = CLAY_PADDING_ALL(16),
				.childGap = global_gap,
			},
		}) {
			// left side bar
			left_side_bar(uiData);

			vline();

			// main content
			main_content(uiData);

			vline();

			// right side bar
			right_side_bar(uiData);
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

