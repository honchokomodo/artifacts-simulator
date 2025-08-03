#include <clay.h>
#include "clay_renderer_raylib.c"
#include <raylib.h>
#include <stddef.h>

typedef struct {
	Clay_Dimensions windowSize;
	Vector2 mousePosition;
	Vector2 scrollDelta;
	bool isLeftMouseDown;
	float frameTime;
	bool state;
	bool showDebug;
	// we will need more stuff here later like character builds
	// and artifact sets plus other useful values
} Interface_Data;

const int FONT_ID_HONCHOKOMONO = 0;
Clay_Color COLOR_WHITE = { 255, 255, 255, 255};
Clay_Color COLOR_PRIMARY = {151, 239, 255, 255}; // blue
Clay_Color COLOR_ACCENT = {2, 215, 255, 255}; // bolder blue
Clay_Color COLOR_BG = {200, 243, 255, 255}; // light blue
Clay_Color COLOR_COMPLEMENT = {255, 190, 2, 255}; // orange-ish color
Clay_Color COLOR_BLACK = { 0, 0, 0, 255};

Clay_Color COLOR_BUTTON_PRIMARY = {50, 132, 232, 255}; // dark blue
void text_large(Clay_String text, Clay_Color color){
	CLAY({
	}){
		CLAY_TEXT(text,
			CLAY_TEXT_CONFIG({
				.fontId = FONT_ID_HONCHOKOMONO,
				.fontSize = 24,
				.textColor = color
			})
		);
	}
}

void text_p(Clay_String text, Clay_Color color){
	CLAY({
	}){
		CLAY_TEXT(text,
			CLAY_TEXT_CONFIG({
				.fontId = FONT_ID_HONCHOKOMONO,
				.fontSize = 18, 
				.textColor = color
			})
		);
	}
}

static void dropdown_menu(Clay_ElementId menu_id, Clay_String items_text[], size_t items_text_len){


	CLAY({
		.id = menu_id,
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = { .width = CLAY_SIZING_PERCENT(1)}
		},
	}){
		for(int i=0; i < items_text_len; i++ ){

			Clay_CornerRadius cornerRadius;
	
			if (i == 0) {
				cornerRadius = (Clay_CornerRadius){4, 4, 0, 0};
			} else if (i == items_text_len - 1) {
				cornerRadius = (Clay_CornerRadius){0, 0, 4, 4};
			} else {
				cornerRadius = (Clay_CornerRadius){0, 0, 0, 0};
			}
	
			CLAY({
				.id = CLAY_SIDI(menu_id.stringId, i),
				.layout = {
					.padding = {4,4,2,2},
					.sizing = {
						.width = CLAY_SIZING_PERCENT(1)
					}
				},
				.cornerRadius = cornerRadius,
				.backgroundColor = COLOR_BG,
				.border = {
					.width = {2,2,1,1},
					.color = COLOR_BUTTON_PRIMARY
				}
			}){
				text_p(items_text[i], COLOR_BLACK);
			}
		}
	}

}

void dropdown_button(Clay_ElementId id, Clay_ElementId menu_id, Clay_String button_text, Clay_String items_text[], size_t items_text_len, bool state){

	CLAY({
		.id = id,
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.childGap = 4,
			.sizing = { .width = CLAY_SIZING_FIXED(150)}
		},
	}){
		CLAY({
			.layout = {
				.padding = {4,4,4,4},
				.sizing = {
					.width = CLAY_SIZING_GROW()
					}
			},
			.cornerRadius = CLAY_CORNER_RADIUS(8),
			.backgroundColor = COLOR_BUTTON_PRIMARY
		}){
			text_p(button_text, COLOR_WHITE);
		}
		if(state){
			dropdown_menu(menu_id, items_text, items_text_len);	
		}
	};
}
