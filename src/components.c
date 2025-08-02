#include <clay.h>
#include "clay_renderer_raylib.c"
#include <raylib.h>

const int FONT_ID_HONCHOKOMONO = 0;
Clay_Color COLOR_WHITE = { 255, 255, 255, 255};
Clay_Color COLOR_PRIMARY = {151, 239, 255, 255}; // blue
Clay_Color COLOR_ACCENT = {2, 215, 255, 255}; // bolder blue
Clay_Color COLOR_BG = {200, 243, 255, 255}; // light blue
Clay_Color COLOR_COMPLEMENT = {255, 190, 2, 255}; // orange-ish color
Clay_Color COLOR_BLACK = { 0, 0, 0, 255};

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

void dropdown(Clay_String menu_text, Clay_String items_text[], size_t items_text_len, Clay_ElementId id){
	CLAY({
		.id = id,
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM
		},
	}){
		CLAY({
			.layout = {.padding = {4,4,4,4}},
			.cornerRadius = CLAY_CORNER_RADIUS(8),
			.backgroundColor = COLOR_ACCENT
		}){
			text_p(menu_text, COLOR_WHITE);
		}
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
					.color = COLOR_ACCENT
				}
			}){
				text_p(items_text[i], COLOR_BLACK);
			}
		}
	};
}