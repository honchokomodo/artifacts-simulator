// vim: ts=2 sw=2
#include "components.c"

typedef struct {
	Clay_Dimensions windowSize;
	Vector2 mousePosition;
	Vector2 scrollDelta;
	bool isLeftMouseDown;
	float frameTime;
	// we will need more stuff here later like character builds
	// and artifact sets plus other useful values
} Interface_Data;

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
			Clay_String test_dropdown[] = {CLAY_STRING("ITEM1"),CLAY_STRING("ITEM2")};
			size_t test_dropdown_len = sizeof(test_dropdown) / sizeof(test_dropdown[0]);
			dropdown(CLAY_STRING("dropdown menu"), test_dropdown, test_dropdown_len, CLAY_ID("dropdown"));
			
		}
	}

	Clay_RenderCommandArray renderCommands = Clay_EndLayout();
	return renderCommands;
}

