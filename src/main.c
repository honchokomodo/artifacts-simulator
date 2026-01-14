#include "layout.c"

void HandleClayErrors(Clay_ErrorData errorData)
{
	printf("%s", errorData.errorText.chars);
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

	Font fonts[1];
	fonts[FONT_ID_HONCHOKOMONO] = LoadFontEx("resources/fonts/honchokomono-regular-normal.otf", 48, NULL, 0);
	SetTextureFilter(fonts[FONT_ID_HONCHOKOMONO].texture, TEXTURE_FILTER_BILINEAR); 
	Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);  

	ic_initcache(599, 1024);
	arena.buf = malloc(16384);

	if (!_ic_table && !_ic_arr && !arena.buf)
		exit(1);

	Interface_Data uiData = uiData_Initialize();

	state = 0;
	sentinel = 0;
    
	while(!WindowShouldClose())
	{
		// prepare data
		uiData.windowSize.width = GetScreenWidth();
		uiData.windowSize.height = GetScreenHeight();
		uiData.mousePosition = GetMousePosition();
		uiData.scrollDelta = GetMouseWheelMoveV();
		uiData.isLeftMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
		uiData.frameTime = GetFrameTime();

		if (IsKeyPressed(KEY_D)) {
			uiData.showDebug = !uiData.showDebug;
		}
		
		Clay_SetDebugModeEnabled(uiData.showDebug);
		Clay_SetLayoutDimensions(uiData.windowSize);

		Clay_SetPointerState(
				(Clay_Vector2) {uiData.mousePosition.x, uiData.mousePosition.y},
				uiData.isLeftMouseDown
				);

		Clay_UpdateScrollContainers(
				true,
				(Clay_Vector2) {uiData.scrollDelta.x, uiData.scrollDelta.y},
				uiData.frameTime
				);

		Clay_RenderCommandArray renderCommands = create_layout(&uiData);

		BeginDrawing();
		ClearBackground(WHITE);

		Clay_Raylib_Render(renderCommands, fonts);

		EndDrawing();
		la_reset(&arena);
	}

	ic_destroycache();
	free(arena.buf);

	Clay_Raylib_Close();
	free(clayMemory.memory);
}
