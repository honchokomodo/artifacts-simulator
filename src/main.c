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


Clay_RenderCommandArray CreateLayout(Clay_Context* context) {
    Clay_SetCurrentContext(context);
    Clay_SetDebugModeEnabled(true);

    // Run once per frame
    Clay_SetLayoutDimensions((Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    });
    Vector2 mousePosition = GetMousePosition();
    Vector2 scrollDelta = GetMouseWheelMoveV();
    Clay_SetPointerState(
        (Clay_Vector2) { mousePosition.x, mousePosition.y},
        IsMouseButtonDown(0)
    );
    Clay_UpdateScrollContainers(
        true,
        (Clay_Vector2) {scrollDelta.x, scrollDelta.y },
        GetFrameTime()
    );
    return Artifact_CreateLayout();
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
    

    Font fonts[1];
    fonts[FONT_ID_HONCHOKOMONO] = LoadFontEx("resources/fonts/honchokomono-regular-normal.otf", 48, 0, 400);
    SetTextureFilter(fonts[FONT_ID_HONCHOKOMONO].texture, TEXTURE_FILTER_BILINEAR);

    
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
	Clay_Initialize(clayMemory, windowSize, errorHandler);
	// load the fonts and include a measure text function here
	// Interface_Data dataTop = uiData_Initialize(); // TODO: probably important?
    
    Clay_Context *clayContext = Clay_Initialize(clayMemory, (Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    }, (Clay_ErrorHandler) { HandleClayErrors });
    // Interface_Data data = uiData_Initialize();
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);
    
    while(!WindowShouldClose())
    {
        Clay_RenderCommandArray renderCommands = CreateLayout(clayContext);
        BeginDrawing();
        ClearBackground(WHITE);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }

	Clay_Raylib_Close();
	free(clayMemory.memory);
}
