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

Interface_Data uiData_Initialize() {
	Interface_Data data = {0};
	return data;
}

typedef struct k_opt_opt {
	int value;
	char * label;
	char * image;
} K_Opt;

const int FONT_ID_HONCHOKOMONO = 0;
const int FONT_ID_HONCHOKOMONO_ITALIC = 1;
const int FONT_ID_HONCHOKOMONO_LIGHT = 2;
const int FONT_ID_HONCHOKOMONO_LIGHT_ITALIC = 3;
const int FONT_ID_HONCHOKOMONO_BOLD = 4;
const int FONT_ID_HONCHOKOMONO_BOLD_ITALIC = 5;

Clay_Color COLOR_TEXT = { 0x00, 0x00, 0x00, 0xff };
Clay_Color COLOR_BG = {0xe6, 0xf8, 0xbd, 255};
Clay_Color COLOR_BG_ALT = {0xff, 0xff, 0xff, 0xff}; //primary
Clay_Color COLOR_BORDER = {0x4a, 0xb6, 0x80, 0xff};   // primary
Clay_Color COLOR_BORDER_SECONDARY = {0xbf, 0xe4, 0xc5, 0xff};  // secondary
Clay_Color COLOR_BUTTON = {0x8f, 0xe4, 0xc5, 0xff};

uint32_t active_element = 0;

Clay_Sizing layoutExpand = {
	.width = CLAY_SIZING_GROW(0),
	.height = CLAY_SIZING_GROW(0)
};

Clay_Sizing layoutWide = {
	.width = CLAY_SIZING_GROW(0),
};

Clay_String ch2str(char const * const s)
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

void text_p(Clay_String text){
	CLAY_TEXT(text,
		CLAY_TEXT_CONFIG({
			.fontId = FONT_ID_HONCHOKOMONO,
			.fontSize = 18, 
			.textColor = COLOR_TEXT,
		})
	);
}

void easy_button(int * dest, int value, bool * sentinel)
{
	/* 
	 * turns any element into a clickable button.
	 * if the element is clicked, assign value to *dest and set *sentinel to true.
	 * see toggle_switch for an example.
	 */

	if (Clay_Hovered() && left_up()) {
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

	CLAY(CLAY_ID_LOCAL("toggle_switch"),{
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
		easy_button(dest, !*dest, sentinel);

		CLAY_AUTO_ID({
			// TODO: un-hardcode these
			.backgroundColor = COLOR_BUTTON,
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
				text_p(ch2str(maintext));
				CLAY({
					// spacer
					.layout.sizing = layoutWide,
				}) {}
			}

			toggle_switch(dest, NULL);
		}

		if (subtext != NULL) {
			text_desc(ch2str(subtext));
		}
	}
}

// this is a dropdown
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
				easy_button(dest, opts[i].value, sentinel);
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
					text_p(ch2str(opts[i].label));
				}
			}
		}
	}
}

void float_slider(Clay_ElementId slider_container_id, float * dest, float min, float max, bool * sentinel)
{
	float trange = max - min;
	float t = (*dest - min) / trange;

	// [a] step 1: draw it
	// [a] step 2: make it interactable
	// [a] step 2a: make it not suck to use
	// [a] step 3: make it pretty
	// [ ] step 3a: make it change if its hovered or active
	// [ ] step 4: make it good

	bool hover = false;

	// ==== begin element declarations
	Clay_ElementDeclaration slider_container_decl = {
		.id = slider_container_id,
		.layout = {
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.sizing = {
				.width = CLAY_SIZING_GROW(0),
				.height = CLAY_SIZING_FIXED(10),
			},
		},
		.cornerRadius = CLAY_CORNER_RADIUS(5),
		.border = {{0xff, 0xff, 0xff, 0xff}, {1, 1, 1, 1}},
	};

	Clay_ElementDeclaration slider_filled_decl = {
		.backgroundColor = {0xff, 0xff, 0xff, 0xff},
		.layout.sizing = {
			.width = CLAY_SIZING_PERCENT(t),
			.height = CLAY_SIZING_GROW(0),
		},
		.cornerRadius = CLAY_CORNER_RADIUS(5),
	};

	Clay_ElementDeclaration slider_knob_decl = {
		.backgroundColor = {0xff, 0xff, 0xff, 0xff},
		.layout.sizing = {
			.width = CLAY_SIZING_FIXED(20),
			.height = CLAY_SIZING_FIXED(20),
		},
		.floating = {
			.attachTo = CLAY_ATTACH_TO_PARENT,
			.attachPoints = {
				.parent = CLAY_ATTACH_POINT_RIGHT_CENTER,
				.element = CLAY_ATTACH_POINT_CENTER_CENTER,
			},
			//.zIndex = 0,
		},
		.cornerRadius = CLAY_CORNER_RADIUS(10),
	};
	// ==== end element declarations

	CLAY(slider_container_decl) {
		if (Clay_Hovered()) hover = true;
		CLAY(slider_filled_decl) {
			CLAY(slider_knob_decl) {
				if (Clay_Hovered()) hover = true;
			}
		}

		if (hover && active_element == 0 && left_down()) {
			active_element = slider_container_id.id;
		}

		if (active_element != slider_container_id.id) {
			continue;
		}

		if (left_up()) {
			active_element = 0;
		}

		Clay_BoundingBox bb = Clay_GetElementData(slider_container_id).boundingBox;
		Clay_Vector2 mousepos = Clay_GetCurrentContext()->pointerInfo.position;
		float tmouse = (mousepos.x - bb.x) / bb.width;
		float value = tmouse * trange + min;
		if (value > max) value = max;
		if (value < min) value = min;

		*dest = value;
		if (sentinel) *sentinel = true;
	}
}

void int_slider(Clay_ElementId id, int * dest, int min, int max, bool * sentinel)
{
	int trange = max - min;
	float t = (*dest - min) / (float) trange;

	// [a] step 1: draw it
	// [a] step 2: make it interactable
	// [a] step 2a: make it not suck to use
	// [ ] step 3: make it pretty
	// [ ] step 3a: make it change if its hovered or active
	// [ ] step 4: make it good

	bool hover = false;

	// ==== begin element declarations
	Clay_ElementDeclaration slider_container_decl = {
		.id = id,
		.layout = {
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.sizing = {
				.width = CLAY_SIZING_GROW(0),
				.height = CLAY_SIZING_FIXED(10),
			},
		},
		.cornerRadius = CLAY_CORNER_RADIUS(5),
		.border = {{0xff, 0xff, 0xff, 0xff}, {1, 1, 1, 1}},
	};

	Clay_ElementDeclaration slider_filled_decl = {
		.backgroundColor = {0xff, 0xff, 0xff, 0xff},
		.layout.sizing = {
			.width = CLAY_SIZING_PERCENT(t),
			.height = CLAY_SIZING_GROW(0),
		},
		.cornerRadius = CLAY_CORNER_RADIUS(5),
	};

	Clay_ElementDeclaration slider_knob_decl = {
		.backgroundColor = {0xff, 0xff, 0xff, 0xff},
		.layout.sizing = {
			.width = CLAY_SIZING_FIXED(20),
			.height = CLAY_SIZING_FIXED(20),
		},
		.floating = {
			.attachTo = CLAY_ATTACH_TO_PARENT,
			.attachPoints = {
				.parent = CLAY_ATTACH_POINT_RIGHT_CENTER,
				.element = CLAY_ATTACH_POINT_CENTER_CENTER,
			},
			//.zIndex = 0,
		},
		.cornerRadius = CLAY_CORNER_RADIUS(10),
	};
	// ==== end element declarations

	CLAY(slider_container_decl) {
		if (Clay_Hovered()) hover = true;
		CLAY(slider_filled_decl) {
			CLAY(slider_knob_decl) {
				if (Clay_Hovered()) hover = true;
			}
		}

		if (hover && active_element == 0 && left_down()) {
			active_element = id.id;
		}

		if (active_element != id.id) {
			continue;
		}

		if (left_up()) {
			active_element = 0;
		}

		Clay_BoundingBox bb = Clay_GetElementData(id).boundingBox;
		Clay_Vector2 mousepos = Clay_GetCurrentContext()->pointerInfo.position;
		float tmouse = (mousepos.x - bb.x) / bb.width;
		int value = (int) roundf(tmouse * trange + min);
		if (value > max) value = max;
		if (value < min) value = min;

		*dest = value;
		if (sentinel) *sentinel = true;
	}
}

#endif