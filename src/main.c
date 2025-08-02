#include "raylib.h"
#include <stdint.h>
#define CLAY_IMPLEMENTATION
#include <clay.h>
#include <clay_renderer_raylib.c>
#include "layout.c"

void HandleClayErrors(Clay_ErrorData errorData)
{
	printf("%s", errorData.errorText.chars);
}

Clay_RenderCommandArray CreateLayout(Clay_Context * context, Interface_Data * data)
{
	Clay_SetCurrentContext(context);
	//Clay_SetDebugModeEnabled(true);

	// Run once per frame
	Clay_SetLayoutDimensions(data->windowSize);

	Clay_SetPointerState(
		(Clay_Vector2) {data->mousePosition.x, data->mousePosition.y},
		data->isLeftMouseDown
	);

	Clay_UpdateScrollContainers(
		true,
		(Clay_Vector2) {data->scrollDelta.x, data->scrollDelta.y},
		data->frameTime
	);

	return Artifact_CreateLayout(data);
}

int main(void)
{
	uint32_t WINDOW_CONFIG_FLAGS = 0
		| FLAG_WINDOW_RESIZABLE
		// FLAG_WINDOW_HIGHDPI
		// FLAG_WINDOW_MSAA_4X_HINT
		// FLAG_VSYNC_HINT
	;

	Clay_Raylib_Initialize(1024, 768, "Artifact Simulator", WINDOW_CONFIG_FLAGS);
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

	Font fonts[2];
	fonts[FONT_ID_BODY_16] = LoadFontEx("../resources/fonts/honchokomono-regular-normal.otf", 48, NULL, 0);
	fonts[FONT_ID_H1_24] = LoadFontEx("../resources/fonts/honchokomono-regular-normal.otf", 48, NULL, 0);
	/* probably important?
	SetTextureFilter(fonts[FONT_ID_BODY_16].texture, TEXTURE_FILTER_BILINEAR);
	SetTextureFilter(fonts[FONT_ID_H1_24].texture, TEXTURE_FILTER_BILINEAR);
	*/
	// include a measure text function here
	Interface_Data uiData = uiData_Initialize();
    
	while(!WindowShouldClose())
	{
		// prepare data
		uiData.windowSize.width = GetScreenWidth();
		uiData.windowSize.height = GetScreenHeight();
		uiData.mousePosition = GetMousePosition();
		uiData.scrollDelta = GetMouseWheelMoveV();
		uiData.isLeftMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
		uiData.frameTime = GetFrameTime();

		Clay_RenderCommandArray renderCommands = CreateLayout(clayContext, &uiData);

		BeginDrawing();
		ClearBackground(WHITE);

		Clay_Raylib_Render(renderCommands, fonts);

		EndDrawing();
	}

	Clay_Raylib_Close();
	free(clayMemory.memory);
}
