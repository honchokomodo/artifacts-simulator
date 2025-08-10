#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>
#define CLAY_IMPLEMENTATION
#include "layout.c"

void HandleClayErrors(Clay_ErrorData errorData)
{
	printf("%s", errorData.errorText.chars);
}

Clay_RenderCommandArray CreateLayout(Clay_Context * context, Interface_Data * data)
{
	Clay_SetCurrentContext(context);

	Clay_SetDebugModeEnabled(data->showDebug);

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

	Font fonts[1];
	fonts[FONT_ID_HONCHOKOMONO] = LoadFontEx("resources/fonts/honchokomono-regular-normal.otf", 48, NULL, 0);
	SetTextureFilter(fonts[FONT_ID_HONCHOKOMONO].texture, TEXTURE_FILTER_BILINEAR);
	Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);  

	yoimiya_img = LoadImage("resources/images/characters/yoimiya_portrait.png");

	Background_Item_5_Star = LoadImage("resources/images/Background_Item_5_Star.png");
	Thundering_Pulse_img = LoadImage("resources/images/weapons/thundering_pulse_icon.png");

	yoimiya_img_tex = LoadTextureFromImage(yoimiya_img);

	Background_Item_5_Star_tex = LoadTextureFromImage(Background_Item_5_Star);
	Thundering_Pulse_img_tex = LoadTextureFromImage(Thundering_Pulse_img);

	UnloadImage(yoimiya_img);
	UnloadImage(Background_Item_5_Star);
	UnloadImage(Thundering_Pulse_img);

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

		if(IsKeyPressed(KEY_D)){
			uiData.showDebug = !uiData.showDebug;
		}
		
		Clay_String dropdownIds[][2] = {
			{CLAY_STRING("SANDS_Button"), CLAY_STRING("SANDS_Menu")},
			{CLAY_STRING("GOBLET_Button"), CLAY_STRING("GOBLET_Menu")},
			{CLAY_STRING("CIRCLET_Button"), CLAY_STRING("CIRCLET_Menu")}
		};
		size_t dropdownIdsLens = sizeof(dropdownIds) / sizeof(dropdownIds[0]);

		for(int i = 0; i<dropdownIdsLens; i++){
			if(Clay_PointerOver(Clay_GetElementId(dropdownIds[i][0])) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
				uiData.state[i] = 
				(Clay_PointerOver(Clay_GetElementId(dropdownIds[i][0])))
				|| Clay_PointerOver(Clay_GetElementId(dropdownIds[i][1]));
			}else if(!Clay_PointerOver(Clay_GetElementId(dropdownIds[i][0])) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
				uiData.state[i] = false;
			}
		}

		Clay_RenderCommandArray renderCommands = CreateLayout(clayContext, &uiData);

		BeginDrawing();
		ClearBackground(WHITE);

		Clay_Raylib_Render(renderCommands, fonts);

		EndDrawing();
	}

	Clay_Raylib_Close();
	free(clayMemory.memory);
}
