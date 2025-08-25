#include <stdio.h>
#include <stdlib.h>

#include "../character_ui.c"

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

	CharacterStats amber = CHARACTER_NEW(AMBER,
			.level = 90,
			.constellation = 6,
			.talent = {9, 9, 9});

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
			.backgroundColor = {0x3F, 0x3F, 0x57, 0xFF},
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
			CharacterUIArgs args = {amber};
			character2ui[amber.type](args);
		}

		Clay_RenderCommandArray renderCommands = Clay_EndLayout();

		BeginDrawing();
		ClearBackground(BLACK);

		Clay_Raylib_Render(renderCommands, &font);

		EndDrawing();
	}

	Clay_Raylib_Close();
	free(clayMemory.memory);
	return 0;
}

