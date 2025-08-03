// vim: ts=2 sw=2
#include "components.c"
#include "artifact.c"

Interface_Data uiData_Initialize() {
	Interface_Data data = {0};
	return data;
}

Clay_RenderCommandArray Artifact_CreateLayout(Interface_Data *data) {
	Clay_Sizing layoutExpand = {
		.width = CLAY_SIZING_GROW(0),
		.height = CLAY_SIZING_GROW(0)
	};

	Clay_BeginLayout();

	//Build UI here
	CLAY({
		.id = CLAY_ID("OuterContainer"),
		.backgroundColor = COLOR_BG,
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = layoutExpand,
			.padding = CLAY_PADDING_ALL(16),
			.childGap = 16
		}
	}) {
	// Child elements
		CLAY({
			.id = CLAY_ID("TitleBar"),
			.layout = {
				.sizing = {
					.height = CLAY_SIZING_FIXED(60),
					.width = CLAY_SIZING_GROW(0)
				},
				.padding = {16,16,0,0},
				.childGap = 16,
				.childAlignment = {
					.y = CLAY_ALIGN_Y_CENTER
				}
			},
			.backgroundColor = COLOR_PRIMARY,
			.cornerRadius = CLAY_CORNER_RADIUS(8),
			.border = {
				.color = COLOR_ACCENT,
				.width = {2,2,2,2}
			}
		}) {
			text_large(CLAY_STRING("Artifact Smulator for Genshin Impact"), COLOR_BLACK);
		}

		CLAY({
			.id = CLAY_ID("Inputs"),
			.layout = {
				.sizing = layoutExpand,
				.childGap = 16,
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.padding = CLAY_PADDING_ALL(16)
			},
			.clip = {
					.vertical = true,
					.childOffset = Clay_GetScrollOffset()
			},
			.backgroundColor = COLOR_WHITE,
			.cornerRadius = CLAY_CORNER_RADIUS(8),
			.border = {
				.color = COLOR_ACCENT,
				.width = {2,2,2,2}
			}
		}) {
			// put stuff here
			text_large(CLAY_STRING("INPUTS"),COLOR_BLACK);
			text_p(CLAY_STRING("Input main stats:"), COLOR_BLACK); 
			
			Clay_String SANDS_select[] = {
				CLAY_STRING("HP_PERCENT"),
				CLAY_STRING("ATK_PERCENT"),
				CLAY_STRING("DEF_PERCENT"),
				CLAY_STRING("ENERGY_RECHARGE"),
				CLAY_STRING("ELEMENTAL_MASTERY")
			};

			size_t select_lens[] = {
				[SANDS] = sizeof(SANDS_select) / sizeof(SANDS_select[0])
			};
			
			dropdown_button(CLAY_ID("SANDS_Button"), CLAY_ID("SANDS_Menu"), CLAY_STRING("SANDS"), SANDS_select, select_lens[SANDS], data->state);
			
		}
	}

	Clay_RenderCommandArray renderCommands = Clay_EndLayout();
	return renderCommands;
}

