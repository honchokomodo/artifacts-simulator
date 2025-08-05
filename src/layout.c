// vim: ts=2 sw=2
#include "components.c"
#include "artifact.c"


Interface_Data uiData_Initialize() {
	Interface_Data data = {0};
	return data;
}

Clay_RenderCommandArray Artifact_CreateLayout(Interface_Data *data) {
	Clay_String SANDS_select[] = {
		CLAY_STRING("HP_PERCENT"),
		CLAY_STRING("ATK_PERCENT"),
		CLAY_STRING("DEF_PERCENT"),
		CLAY_STRING("ENERGY_RECHARGE"),
		CLAY_STRING("ELEMENTAL_MASTERY")
	};

	Clay_String GOBLET_select[] = {
		CLAY_STRING("HP_PERCENT"),
		CLAY_STRING("ATK_PERCENT"),
		CLAY_STRING("DEF_PERCENT"),
		CLAY_STRING("ELEMENTAL_MASTERY"),
		CLAY_STRING("ELEMENTAL_DMG"),
		CLAY_STRING("PHYSICAL_DMG")
	};

	Clay_String CIRCLET_select[] = {
		CLAY_STRING("HP_PERCENT"),
		CLAY_STRING("ATK_PERCENT"),
		CLAY_STRING("DEF_PERCENT"),
		CLAY_STRING("ELEMENTAL_MASTERY"),
		CLAY_STRING("CRIT_RATE"),
		CLAY_STRING("CRIT_DMG"),
		CLAY_STRING("HEALING_BONUS")
	};

	size_t select_lens[] = {
		[SANDS] = sizeof(SANDS_select) / sizeof(SANDS_select[0]),
		[GOBLET] = sizeof(GOBLET_select) / sizeof(GOBLET_select[0]),
		[CIRCLET] = sizeof(CIRCLET_select) / sizeof(CIRCLET_select[0])
	};

	Clay_Sizing layoutExpand = {
		.width = CLAY_SIZING_GROW(0),
		.height = CLAY_SIZING_GROW(0)
	};

	Clay_BeginLayout();

	//Build UI here
	CLAY({
		.backgroundColor = COLOR_BG,
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = layoutExpand,
			.padding = CLAY_PADDING_ALL(16),
			.childGap = 12
		}
	}) {
	// Child elements
		CLAY({
			.id = CLAY_ID("Title Bar"),
			.layout = {
				.sizing = {
					.height = CLAY_SIZING_PERCENT(0.05),
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

		CLAY({ .layout = { .layoutDirection = CLAY_LEFT_TO_RIGHT, .childAlignment = CLAY_ALIGN_X_CENTER, .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.35)}, .childGap = 8} }){
			CLAY({
				.id = CLAY_ID("Character Image"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4}
				},
				// .cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BUTTON_PRIMARY,
					.width = {2,2,2,2}
				},
				.image = { .imageData = &yoimiya_tex },
				.aspectRatio = (float) yoimiya.width / yoimiya.height,
			}){
				// text_sub_heading(CLAY_STRING("Character Image"), COLOR_BLACK);
				// CLAY({ .image = { .imageData = &yoimiya_tex }, .aspectRatio = (float) yoimiya.width / yoimiya.height }){};
			};

			CLAY({
				.id = CLAY_ID("Character Summary"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.25), .height = CLAY_SIZING_PERCENT(0.8)},
					.padding = {8, 8, 4, 4}
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Character Summary"), COLOR_BLACK);
			};

			CLAY({
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.25), .height = CLAY_SIZING_PERCENT(0.8)},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				},
				// .image = { .imageData = &Thundering_Pulse_tex },
				// .aspectRatio = (float) Thundering_Pulse.width / Thundering_Pulse.height,	
			}){
				// text_sub_heading(CLAY_STRING("Weapon Profile"), COLOR_BLACK);
				CLAY({
					.layout = { 
						// .childAlignment = CLAY_ALIGN_X_CENTER, 
						.sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW()},
						// .padding = {8, 8, 4, 4},
					},
					.border = { .width = {2,2,2,2}, .color = COLOR_BUTTON_PRIMARY,  },
					.image = { .imageData = &Background_Item_5_Star_tex },
					.aspectRatio = (float) Background_Item_5_Star.width / Background_Item_5_Star.height,
				}){
					CLAY({
						.layout = { 
							// .childAlignment = CLAY_ALIGN_X_CENTER, 
							.sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW()},
							// .padding = {8, 8, 4, 4},
						},
						.border = { .width = {2,2,2,2}, .color = COLOR_BUTTON_PRIMARY,  },
						.image = { .imageData = &Thundering_Pulse_tex },
						.aspectRatio = (float) Thundering_Pulse.width / Thundering_Pulse.height,
					}){};
				}
			};

			CLAY({
				.id = CLAY_ID("Artifact Set Selection"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.25), .height = CLAY_SIZING_PERCENT(0.8)},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				},
			}){
				text_sub_heading(CLAY_STRING("Artifact Set Selection"), COLOR_BLACK);
				
			};
			
		};

		CLAY({.layout = { .layoutDirection = CLAY_LEFT_TO_RIGHT, .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.25)}, .childGap = 8} }){
			CLAY({
				.id = CLAY_ID("Flower"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.2), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Flower"), COLOR_BLACK);
			};

			CLAY({
				.id = CLAY_ID("Feather"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.2), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Feather"), COLOR_BLACK);

			};

			CLAY({
				.id = CLAY_ID("Sands"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.2), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				}
			}){
				// text_sub_heading(CLAY_STRING("Sands"), COLOR_BLACK);
				dropdown_button(CLAY_ID("SANDS_Button"), CLAY_ID("SANDS_Menu"), CLAY_STRING("SANDS"), SANDS_select, select_lens[SANDS], data->state[0]);
			};

			CLAY({
				.id = CLAY_ID("Goblet"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.2), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				}
			}){
				// text_sub_heading(CLAY_STRING("Goblet"), COLOR_BLACK);
				dropdown_button(CLAY_ID("GOBLET_Button"), CLAY_ID("GOBLET_Menu"), CLAY_STRING("GOBLET"), GOBLET_select, select_lens[GOBLET], data->state[1]);
			};

			CLAY({
				.id = CLAY_ID("Circlet"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.layoutDirection = CLAY_TOP_TO_BOTTOM,
					.sizing = { .width = CLAY_SIZING_PERCENT(0.2), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				}
			}){
				dropdown_button(CLAY_ID("CIRCLET_Button"), CLAY_ID("CIRCLET_Menu"), CLAY_STRING("CIRCLET"), CIRCLET_select, select_lens[CIRCLET], data->state[2]);
				// text_sub_heading(CLAY_STRING("Circlet"), COLOR_BLACK);
			};
		};

		CLAY({.layout = { .layoutDirection = CLAY_LEFT_TO_RIGHT, .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() }, .childGap = 8}}){
			CLAY({
				.id = CLAY_ID("Graph"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.25), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Build Score Graph"), COLOR_BLACK);
			};

			CLAY({
				.id = CLAY_ID("Grade"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.25), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Artifact Grade"), COLOR_BLACK);
			};

			CLAY({
				.id = CLAY_ID("Inventory"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_WHITE,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_ACCENT,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Inventory"), COLOR_BLACK);
			};
		}
	}

	Clay_RenderCommandArray renderCommands = Clay_EndLayout();
	return renderCommands;
}

