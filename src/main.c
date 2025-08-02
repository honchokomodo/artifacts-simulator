#include "raylib.h"
#include <stdint.h>
#define CLAY_IMPLEMENTATION
#include <clay.h>
#include <clay_renderer_raylib.c>
#include "layout.c"

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

Clay_RenderCommandArray CreateLayout(Clay_Context* context, Interface_Data *data) {
    Clay_SetCurrentContext(context);
    Clay_SetDebugModeEnabled(true);

    // Run once per frame
    Clay_SetLayoutDimensions((Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    });
    Vector2 mousePosition = GetMousePosition();
    mousePosition.y -= data->yOffset;
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
    return Artifact_CreateLayout(data);
}

int main(void){
    documents.documents = (Document[]) {
        { .title = CLAY_STRING("title"), .contents = CLAY_STRING("aaaaaa")}
    };
    Clay_Raylib_Initialize(1024, 768, "Artifact Simulator", FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    SetTargetFPS(30);

    Font fonts[2];
    fonts[FONT_ID_BODY_16] = LoadFontEx("resources/fonts/honchokomono-regular-normal.otf", 48, 0, 400);
    fonts[FONT_ID_H1_24] = LoadFontEx("resources/fonts/honchokomono-regular-normal.otf", 48, 0, 400);
    SetTextureFilter(fonts[FONT_ID_BODY_16].texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonts[FONT_ID_H1_24].texture, TEXTURE_FILTER_BILINEAR);

    uint64_t clayRequiredMemory = Clay_MinMemorySize();

    Clay_Arena clayMemoryTop = Clay_CreateArenaWithCapacityAndMemory(clayRequiredMemory, malloc(clayRequiredMemory));
    Clay_Context *clayContextTop = Clay_Initialize(clayMemoryTop, (Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight() /2.0
    }, (Clay_ErrorHandler) { HandleClayErrors });
    Interface_Data dataTop = uiData_Initialize();
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    Clay_Arena clayMemoryBottom = Clay_CreateArenaWithCapacityAndMemory(clayRequiredMemory, malloc(clayRequiredMemory));
    Clay_Context *clayContextBottom = Clay_Initialize(clayMemoryBottom, (Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight() / 2.0
    }, (Clay_ErrorHandler) { HandleClayErrors });
    Interface_Data dataBottom = uiData_Initialize();
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);
    
    while(!WindowShouldClose())
    {
        dataBottom.yOffset = GetScreenHeight() / 2.0;
        Clay_RenderCommandArray renderCommands = CreateLayout(clayContextTop, &dataTop);
        BeginDrawing();
        ClearBackground(WHITE);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }
    Clay_Raylib_Close();
}