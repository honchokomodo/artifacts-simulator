#include <stdio.h>
#include <stdlib.h>

#include "../components.c"

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

	int state = 0;
	float floatstate = 2;
	float floatstate2 = 2;
	bool dropdowndown = 0;
	bool sentinel = 0;

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
			.backgroundColor = {0x23, 0x3F, 0x57, 0xFF},
			.layout = {
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing = {
					.width = CLAY_SIZING_GROW(0),
					.height = CLAY_SIZING_GROW(0),
				},
				.padding = CLAY_PADDING_ALL(16),
				.childGap = 12,
			}
		}) {
			Clay_Color green = {0x00, 0xff, 0x00, 0xff};
			Clay_Color red = {0xff, 0x00, 0x00, 0xff};

			text_large(ch2str(la_strfmt(&arena, "state: %d", state)));
			text_large(ch2str(la_strfmt(&arena, "floatstate: %g", floatstate)));

			Texture2D * icon = ic_get_tex("resources/images/characters/character_nothing_icon.png");
			CLAY({
				.layout.sizing = {
					.width = CLAY_SIZING_FIXED(100),
					.height = CLAY_SIZING_FIXED(100),
				},
				.image.imageData = icon,
				.aspectRatio = icon->width / (float) icon->height,
			}) {}

			CLAY({
				.backgroundColor = COLOR_BG,
				.layout.sizing = {
					.width = CLAY_SIZING_FIXED(100),
					.height = CLAY_SIZING_FIXED(100),
				},
			}) {
				easy_button(&state, 1, &sentinel);
			}

			toggle_switch(&state, &sentinel);
			toggle_switch_text(&state, "maintext", "subtext", &sentinel);

			int k = 5;
			K_Opt opts[5];
			for (int i = 0; i < k; i++) {
				opts[i].value = i;
				opts[i].label = la_strfmt(&arena, "option %d", i);
				opts[i].image = "resources/images/characters/character_nothing_icon.png";
			}

			CLAY({
				.backgroundColor = interactable_color(),
				.layout = {
					.layoutDirection = CLAY_LEFT_TO_RIGHT,
					.padding = CLAY_PADDING_ALL(3),
					.childGap = 3,
					.childAlignment.y = CLAY_ALIGN_Y_CENTER,
				},
			}) {
				if (opts[state].image != NULL) {
					Texture2D * tex = ic_get_tex(opts[state].image);
					CLAY({
						.layout.sizing = {
							.width = CLAY_SIZING_FIXED(30),
							.height = CLAY_SIZING_FIXED(30),
						},
						.image.imageData = tex,
						.aspectRatio = tex->width / (float) tex->height,
					}) {}
				}

				if (opts[state].label != NULL) {
					// assume that the strings are saved
					text_p(ch2str(opts[state].label));
				}
				k_opt_list(&state, k, opts, &dropdowndown, &sentinel);
			}

			float_slider(CLAY_ID("slider 1"), &floatstate, 0, 4, &sentinel);
			float_slider(CLAY_ID("slider 2"), &floatstate2, 0, 4, &sentinel);
			int_slider(CLAY_ID("slider 3"), &state, 0, 4, &sentinel);

			CLAY({.layout.sizing = layoutExpand}) {}

			text_large(ch2str(la_strfmt(&arena, "%zu", arena.offset)));
		}

		Clay_RenderCommandArray renderCommands = Clay_EndLayout();

		BeginDrawing();
		ClearBackground(BLACK);

		Clay_Raylib_Render(renderCommands, &font);

		EndDrawing();
		la_reset(&arena);
		sentinel = 0;
	}

	ic_destroycache();
	free(arena.buf);

	UnloadFont(font);
	Clay_Raylib_Close();
	free(clayMemory.memory);
	return 0;
}

