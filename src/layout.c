// vim: ts=2 sw=2
#include "components.c"
#include "scenario.c"
#include "artifact_ui.c"
#include "character_ui.c"
#include "../build/include/weapons_ui.c"

Clay_RenderCommandArray create_layout(Interface_Data *data) {
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

	Texture2D * yoimiya_img_tex = ic_get_tex("resources/images/characters/yoimiya_portrait.png");

	Texture2D * Background_Item_5_Star_tex = ic_get_tex("resources/images/Background_Item_5_Star.png");
	Texture2D * Thundering_Pulse_img_tex = ic_get_tex("resources/images/weapons/thundering_pulse_icon.png");

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
			.backgroundColor = COLOR_BG_ALT,
			.cornerRadius = CLAY_CORNER_RADIUS(8),
			.border = {
				.color = COLOR_BORDER,
				.width = {2,2,2,2},
			}
		}) {
			text_large(CLAY_STRING("Artifact Simulator for Genshin Impact"));
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
					.color = COLOR_BUTTON,
					.width = {2,2,2,2}
				},
				.image = { .imageData = yoimiya_img_tex },
				.aspectRatio = (float) yoimiya_img_tex->width / yoimiya_img_tex->height,
			}){};

			CLAY({
				.id = CLAY_ID("Character Summary"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.25), .height = CLAY_SIZING_PERCENT(0.8)},
					.padding = {8, 4, 4, 4}
				},
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
					.width = {2,2,2,2}
				}
			}){
				// text_sub_heading(character2str[YOIMIYA], COLOR_WHITE);
			};

			CLAY({
				.layout = { 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.25), .height = CLAY_SIZING_PERCENT(0.8)},
					.padding = {8,2,8,8},
					.childAlignment = {0, CLAY_ALIGN_Y_CENTER},
					.layoutDirection = CLAY_TOP_TO_BOTTOM,
				},
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
					.width = {2,2,2,2}
				},
			}){
				CLAY({ .layout = { .sizing = { .width = CLAY_SIZING_GROW() }}}){
					CLAY({
						.layout = { 
							.sizing = { .width = CLAY_SIZING_PERCENT(0.33), .height = CLAY_SIZING_GROW()},
						},
						.border = { .width = {2,2,2,2}, .color = COLOR_BUTTON  },
						.image = { .imageData = Background_Item_5_Star_tex },
						.aspectRatio = (float) Background_Item_5_Star_tex->width / Background_Item_5_Star_tex->height,
					}){
						CLAY({
							.layout = { 
								.sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW()},
							},
							.border = { .width = {2,2,2,2}, .color = COLOR_BUTTON  },
							.image = { .imageData = Thundering_Pulse_img_tex },
							.aspectRatio = (float) Thundering_Pulse_img_tex->width / Thundering_Pulse_img_tex->height,
						}){};
					}
	
					CLAY({
						.layout = { 
							.sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
							.layoutDirection = 	CLAY_TOP_TO_BOTTOM,
							.childAlignment = CLAY_ALIGN_X_CENTER,
						},
					}){
						text_sub_heading1(ch2str(weapon2str[THUNDERING_PULSE]));
	
						CLAY({ .layout = { .childAlignment = {CLAY_ALIGN_X_LEFT, CLAY_ALIGN_Y_BOTTOM}, .layoutDirection = CLAY_LEFT_TO_RIGHT } }){
							text_p(CLAY_STRING("Lvl: ") );
							text_large(ch2str("test"));
						}
	
						CLAY({ .layout = { .layoutDirection = CLAY_LEFT_TO_RIGHT, .childGap = 32}}){
							CLAY({ .layout = { .childAlignment = CLAY_ALIGN_X_LEFT, .layoutDirection = CLAY_TOP_TO_BOTTOM,} } ){
								text_p(ch2str("ATK"));
								text_p(ch2str("HARDCODED STRING"));
							};
							CLAY({ .layout = { .childAlignment = CLAY_ALIGN_X_RIGHT, .layoutDirection = CLAY_TOP_TO_BOTTOM,} } ){
								text_p(ch2str("HARDCODED STRING"));
								text_p(ch2str("HARDCODED STRING"));
							};
						};
					};

				};

				CLAY({
					.layout = {
						.sizing = { .width = CLAY_SIZING_GROW(), },
						.layoutDirection = CLAY_TOP_TO_BOTTOM,
						.padding = {0,0,4,0}
					},
				}){
					text_sub_heading1(ch2str("Rule By Thunder"));
					CLAY({ .clip = { .vertical = true, .childOffset = Clay_GetScrollOffset() },}){
						text_desc(ch2str("Increases ATK by 20~40% and grants the might of the Thunder Emblem. At stack levels 1/2/3, the Thunder Emblem increases Normal Attack DMG by 12/24/40~24/48/80%. The character will obtain 1 stack of Thunder Emblem in each of the following scenarios: Normal Attack deals DMG (stack lasts 5s), casting Elemental Skill (stack lasts 10s); Energy is less than 100% (stack disappears when Energy is full). Each stack's duration is calculated independently."));
					}
				};

			};

			CLAY({
				.id = CLAY_ID("Artifact Set Selection"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.25), .height = CLAY_SIZING_PERCENT(0.8)},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
					.width = {2,2,2,2}
				},
			}){
				text_sub_heading(CLAY_STRING("Artifact Set Selection"));
				
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
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Flower"));
			};

			CLAY({
				.id = CLAY_ID("Feather"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.2), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Feather"));

			};

			CLAY({
				.id = CLAY_ID("Sands"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.2), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
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
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
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
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
					.width = {2,2,2,2}
				}
			}){
				dropdown_button(CLAY_ID("CIRCLET_Button"), CLAY_ID("CIRCLET_Menu"), CLAY_STRING("CIRCLET"), CIRCLET_select, select_lens[CIRCLET], data->state[2]);
				// text_sub_heading(CLAY_STRING("Circlet"));
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
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Build Score Graph"));
			};

			CLAY({
				.id = CLAY_ID("Grade"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_PERCENT(0.25), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Artifact Grade"));
			};

			CLAY({
				.id = CLAY_ID("Inventory"),
				.layout = { 
					.childAlignment = CLAY_ALIGN_X_CENTER, 
					.sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW()},
					.padding = {8, 8, 4, 4},
				},
				.backgroundColor = COLOR_BG_ALT,
				.cornerRadius = CLAY_CORNER_RADIUS(8),
				.border = {
					.color = COLOR_BORDER,
					.width = {2,2,2,2}
				}
			}){
				text_sub_heading(CLAY_STRING("Inventory"));
			};
		}
	}

	Clay_RenderCommandArray renderCommands = Clay_EndLayout();
	return renderCommands;
}

