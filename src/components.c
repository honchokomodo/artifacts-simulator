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

typedef struct k_opt_opt {
	int value;
	char * label;
	char * image;
} K_Opt;

Interface_Data uiData_Initialize() {
	Interface_Data data = {0};
	return data;
}

// TODO perhaps use different font ids for text formatting
// like boldface, italic, etc?
const int FONT_ID_HONCHOKOMONO = 0;

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

Clay_Sizing layoutWide = {
	.width = CLAY_SIZING_GROW(0),
};

Clay_String ch2str(char * s)
{
	return (Clay_String) {
		.chars = s,
		.length = strlen(s),
	};
}

bool left_down() {
	Clay_Context * context = Clay_GetCurrentContext();
	return context->pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME;
}

bool left_hold() {
	Clay_Context * context = Clay_GetCurrentContext();
	return context->pointerInfo.state == CLAY_POINTER_DATA_PRESSED;
}

bool left_up() {
	Clay_Context * context = Clay_GetCurrentContext();
	return context->pointerInfo.state == CLAY_POINTER_DATA_RELEASED_THIS_FRAME;
}

Clay_Color interactable_color(void)
{
	Clay_Color nothing = {0};
	Clay_Color press = {0xFF, 0xFF, 0xFF, 0x20};
	Clay_Color hover = {0xFF, 0xFF, 0xFF, 0x40};

	if (!Clay_Hovered())
		return nothing;

	if (left_hold())
		return press;

	return hover;
}

void text_large(Clay_String text, Clay_Color color)
{
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

void assign_button(int * dest, int value, bool * sentinel)
{
	/* 
	 * turns any element into a clickable button.
	 * if the element is clicked, assign value to *dest and set *sentinel to true.
	 * see toggle_switch for an example.
	 */

	bool hovered = Clay_Hovered();
	Clay_Context * context = Clay_GetCurrentContext();
	bool left_click = context->pointerInfo.state == CLAY_POINTER_DATA_RELEASED_THIS_FRAME;

	if (hovered && left_click) {
		*dest = value;

		if (sentinel) {
			*sentinel = true;
		}
	}
}

void toggle_switch(int * dest, bool * sentinel)
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
		// turn the switch into a clickable button
		assign_button(dest, !*dest, sentinel);

		CLAY({
			// TODO: un-hardcode these
			.backgroundColor = COLOR_BUTTON_PRIMARY,
			.layout.sizing = {
				.width = CLAY_SIZING_FIXED(10),
				.height = CLAY_SIZING_FIXED(10),
			}
		}) {}
	}
}

void toggle_switch_text(int * dest, char * maintext, char * subtext, bool * sentinel)
{
	/*
	 * char * is used instead of Clay_String to allow for null checking.
	 * i.e, if maintext or subtext are NULL, just don't draw them.
	 * this may possibly lead to performance issues later down the line,
	 * but it shouldn't be too much as whatever function is rendering the
	 * text will have to loop over every character anyway.
	 */

	//TODO: possibly make this file-scope instead of function-scope
	
	CLAY({
		// The container for the switch element
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.sizing = layoutWide,
			.padding = CLAY_PADDING_ALL(16), //TODO: un-hardcode
			.childGap = 12, //TODO: un-hardcode this
		},
	}) {
		CLAY({
			// text and toggle
			.layout = {
				.layoutDirection = CLAY_LEFT_TO_RIGHT,
				.sizing = layoutWide,
				// no padding
				.childGap = 12, // TODO: un-hardcode this
				.childAlignment.y = CLAY_ALIGN_Y_CENTER,
			}
		}) {
			if (maintext != NULL) {
				// maintext
				text_p(ch2str(maintext), COLOR_WHITE);
				CLAY({
					// spacer
					.layout.sizing = layoutWide,
				}) {}
			}

			toggle_switch(dest, NULL);
		}

		if (subtext != NULL) {
			text_desc(ch2str(subtext), COLOR_WHITE);
		}
	}
}

void k_opt_list(int * dest, int k, K_Opt * opts, bool * drop, bool * sentinel)
{
	bool just_dropped = 0;

	if (Clay_Hovered() && left_down()) {
		*drop = !*drop;
		just_dropped = true;
	}

	if (!*drop) {
		return;
	}

	CLAY({ // main container config
		.backgroundColor = COLOR_BG,
		.layout = {
			.layoutDirection = CLAY_TOP_TO_BOTTOM,
			.childGap = 1,
		},
		.floating = {
			.attachTo = CLAY_ATTACH_TO_PARENT,
			.attachPoints = {
				.parent = CLAY_ATTACH_POINT_CENTER_BOTTOM,
				.element = CLAY_ATTACH_POINT_CENTER_TOP,
			},
		},
	}) {
		if (!Clay_Hovered() && left_down() && !just_dropped) {
			*drop = false;
		}

		for (int i = 0; i < k; i++) {
			CLAY({ // opt element config
				.backgroundColor = interactable_color(),
				.layout = {
					.layoutDirection = CLAY_LEFT_TO_RIGHT,
					.padding = CLAY_PADDING_ALL(3),
					.childGap = 3, // TODO: un-hardcode
					.childAlignment.y = CLAY_ALIGN_Y_CENTER,
				},
			}) {
				assign_button(dest, opts[i].value, sentinel);
				if (*sentinel) {
					*drop = false;
				}
				if (opts[i].image != NULL) {
					Texture2D * tex = ic_get_tex(opts[i].image);
					CLAY({
						.layout.sizing = {
							.width = CLAY_SIZING_FIXED(30),
							.height = CLAY_SIZING_FIXED(30),
						},
						.image.imageData = tex,
						.aspectRatio = tex->width / (float) tex->height,
					}) {}
				}

				if (opts[i].label != NULL) {
					// assume that the strings are saved
					text_p(ch2str(opts[i].label), COLOR_WHITE);
				}
			}
		}
	}
}

#endif
