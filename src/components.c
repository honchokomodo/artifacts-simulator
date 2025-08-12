// vim: ts=2 sw=2
#ifndef COMPONENTS_C
#define COMPONENTS_C

#define CLAY_IMPLEMENTATION
#include <clay.h>
#include "clay_renderer_raylib.c"
#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "utils/linear_allocator.c"
#include "utils/image_cache.c"

// TODO: make this a function instead of a macro
#define CLAY_STR(s) (CLAY__INIT(Clay_String) {.length = strlen(s), .chars = s})

typedef struct {
	Clay_Dimensions windowSize;
	Vector2 mousePosition;
	Vector2 scrollDelta;
	bool isLeftMouseDown;
	float frameTime;
	bool showDebug;
	bool state[3]; // this doesn't feel right
         // we should find a way to remove the bools array
         // but if we find that we have to keep them its fine
	// we will need more stuff here later like character builds
	// and artifact sets plus other useful values
} Interface_Data;

Interface_Data uiData_Initialize() {
	Interface_Data data = {0};
	return data;
}

// TODO perhaps use different font ids for text formatting
// like boldface, italic, etc?
const int FONT_ID_HONCHOKOMONO = 0;

// ========= TODO should not be global, use ic_get_tex(filename) instead
Texture2D yoimiya_img_tex;

Texture2D Background_Item_5_Star_tex;
Texture2D Thundering_Pulse_img_tex;
// =========

Clay_Color COLOR_WHITE = { 255, 255, 255, 255};
Clay_Color COLOR_BLACK = { 0, 0, 0, 255};
Clay_Color COLOR_PRIMARY = {46, 46, 78, 255}; // blue
Clay_Color COLOR_ACCENT = {215, 182, 91, 255}; 
Clay_Color COLOR_BG = {63, 63, 87, 255}; 
Clay_Color COLOR_COMPLEMENT = {255, 190, 2, 255}; // orange-ish color

Clay_Color COLOR_BUTTON_PRIMARY = {238, 185, 36, 255}; // dark blue

Clay_Sizing layoutExpand = {
	.width = CLAY_SIZING_GROW(0),
	.height = CLAY_SIZING_GROW(0)
};

void text_large(Clay_String text, Clay_Color color){
	CLAY_TEXT(text,
		CLAY_TEXT_CONFIG({
			.fontId = FONT_ID_HONCHOKOMONO,
			.fontSize = 24,
			.textColor = color
		})
	);
}

void text_sub_heading(Clay_String text, Clay_Color color){
	CLAY_TEXT(text,
		CLAY_TEXT_CONFIG({
			.fontId = FONT_ID_HONCHOKOMONO,
			.fontSize = 22,
			.textColor = color
		})
	);
}

void text_sub_heading1(Clay_String text, Clay_Color color){
	CLAY_TEXT(text,
		CLAY_TEXT_CONFIG({
			.fontId = FONT_ID_HONCHOKOMONO,
			.fontSize = 20,
			.textColor = color,
		})
	);
}

void text_p(Clay_String text, Clay_Color color){
	CLAY_TEXT(text,
		CLAY_TEXT_CONFIG({
			.fontId = FONT_ID_HONCHOKOMONO,
			.fontSize = 18, 
			.textColor = color
		})
	);
}

void text_desc(Clay_String text, Clay_Color color){
	CLAY_TEXT(text,
		CLAY_TEXT_CONFIG({
			.fontId = FONT_ID_HONCHOKOMONO,
			.fontSize = 15, 
			.textColor = color,
			.textAlignment = CLAY_TEXT_ALIGN_LEFT,
		})
	);
}

static void dropdown_menu(Clay_ElementId menu_id, Clay_String items_text[], size_t items_text_len){

	CLAY({
		.id = menu_id,
		.floating = {
			.attachTo = CLAY_ATTACH_TO_PARENT,
            .attachPoints = {
                .parent = CLAY_ATTACH_POINT_CENTER_BOTTOM,
				.element = CLAY_ATTACH_POINT_CENTER_TOP
			},
		}
	}){
		CLAY({
			.layout = {
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing = {
						.width = CLAY_SIZING_FIXED(135)
				},
			},
			.backgroundColor = {40, 40, 40, 255 },
			.cornerRadius = CLAY_CORNER_RADIUS(8)
		}) {
			for(int i=0; i < items_text_len; i++ ){

				Clay_CornerRadius cornerRadius;
				Clay_BorderWidth borderWidth;
		
				if (i == 0) {
					cornerRadius = (Clay_CornerRadius){4, 4, 0, 0};
					borderWidth = (Clay_BorderWidth){2,2,2,1};
				} else if (i == items_text_len - 1) {
					cornerRadius = (Clay_CornerRadius){0, 0, 4, 4};
					borderWidth = (Clay_BorderWidth){2,2,1,2};
				} else {
					cornerRadius = (Clay_CornerRadius){0, 0, 0, 0};
					borderWidth = (Clay_BorderWidth){2,2,1,1};
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
					.backgroundColor = COLOR_ACCENT,
					.border = {
						.width = borderWidth,
						.color = COLOR_WHITE
					}
				}){
					text_p(items_text[i], COLOR_BLACK);
				}
			}
		}
	}

}

void dropdown_button(Clay_ElementId id, Clay_ElementId menu_id, Clay_String button_text, Clay_String items_text[], size_t items_text_len, bool state){

		CLAY({
			.id = id,
			.layout = {
				.padding = {4,4,4,4},
			},
			.backgroundColor = COLOR_BUTTON_PRIMARY,
			.cornerRadius = CLAY_CORNER_RADIUS(8),
		}){
			text_p(button_text, COLOR_WHITE);

			if(state){
				dropdown_menu(menu_id, items_text, items_text_len);	
			}
		}

}

void toggle_switch(int * dest)
{
	/*
	 * *dest is the current state of the switch.
	 * even though this is supposed to be a true/false value,
	 * the location that the state is stored is sizeof(int) bytes big,
	 * so we use int * instead of bool *.
	 *
	 * The switch will handle reading/writing the state to *dest
	 * by doing *dest = value,
	 * with the assumption that true == 1 and false == 0.
	 */

	//TODO: un-hardcode these
	Clay_Color enabledColor = {0x40, 0x80, 0x40, 0xFF};
	Clay_Color disabledColor = {0x00, 0x00, 0x00, 0xFF};

	Clay_Color toggleColor = *dest ?  enabledColor : disabledColor;
	Clay_ChildAlignment toggleSide = {
		.x = *dest ? CLAY_ALIGN_X_RIGHT : CLAY_ALIGN_X_LEFT,
		.y = CLAY_ALIGN_Y_CENTER,
	};

	CLAY({
		.backgroundColor = toggleColor,
		.layout = {
			// TODO: un-hardcode these
			.sizing = {
				.width = CLAY_SIZING_FIXED(20),
				.height = CLAY_SIZING_FIXED(10),
			},
			.childAlignment = toggleSide,
		},
	}) {
		bool hovered = Clay_Hovered();
		Clay_Context * context = Clay_GetCurrentContext();
		bool left_click = context->pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME;

		// user interaction
		if (hovered && left_click) {
			*dest = !*dest;
		}

		CLAY({
			// TODO: un-hardcode these
			.backgroundColor = {0xDD, 0xDD, 0xDD, 0xFF},
			.layout.sizing = {
				.width = CLAY_SIZING_FIXED(10),
				.height = CLAY_SIZING_FIXED(10),
			}
		}) {}
	}
}

void toggle_switch_text(int * dest, char * maintext, char * subtext)
{
	/*
	 * char * is used instead of Clay_String to allow for null checking.
	 * i.e, if maintext or subtext are NULL, just don't draw them.
	 * this may possibly lead to performance issues later down the line,
	 * but it shouldn't be too much as whatever function is rendering the
	 * text will have to loop over every character anyway.
	 */

	//TODO: possibly make this file-scope instead of function-scope
	Clay_Sizing widesize = {
		.width = CLAY_SIZING_GROW(0),
		.height = CLAY_SIZING_FIT(0),
	};
	
	CLAY({
		// The container for the switch element
		.backgroundColor = COLOR_BUTTON_PRIMARY,
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = widesize,
			.padding = CLAY_PADDING_ALL(16), //TODO: un-hardcode
			.childGap = 12, //TODO: un-hardcode this
		},
	}) {
		CLAY({
			// text and toggle
			.backgroundColor = COLOR_BUTTON_PRIMARY,
			.layout = {
				.layoutDirection = CLAY_LEFT_TO_RIGHT,
				.sizing = widesize,
				// no padding
				.childGap = 12, // TODO: un-hardcode this
				.childAlignment = {.y = CLAY_ALIGN_Y_CENTER},
			}
		}) {
			if (maintext != NULL) {
				// maintext
				text_p(CLAY_STR(maintext), COLOR_WHITE);
				CLAY({
					// spacer
					.layout.sizing = widesize,
				}) {}
			}

			toggle_switch(dest);
		}

		if (subtext != NULL) {
			text_desc(CLAY_STR(subtext), COLOR_WHITE);
		}
	}
}

#endif
