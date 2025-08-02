#include <clay.h>
#include <stdint.h>
#include <stdlib.h>

const int FONT_ID_HONCHOKOMONO = 0;
Clay_Color COLOR_WHITE = { 255, 255, 255, 255};
Clay_Color COLOR_ACCENT = {255, 95, 207, 255};
Clay_Color COLOR_BG = {255, 210, 230, 255};
Clay_Color COLOR_BLACK = { 0, 0, 0, 255};

typedef struct {
	Clay_Dimensions windowSize;
	Vector2 mousePosition;
	Vector2 scrollDelta;
	bool isLeftMouseDown;
	float frameTime;
	// we will need more stuff here later like character builds
	// and artifact sets plus other useful values
} Interface_Data;

Interface_Data uiData_Initialize() {
	Interface_Data data = {0};
	return data;
}

Clay_RenderCommandArray Artifact_CreateLayout(Interface_Data *data) {
	Clay_BeginLayout();

	Clay_Sizing layoutExpand = {
		.width = CLAY_SIZING_GROW(0),
		.height = CLAY_SIZING_GROW(0)
	};

    //Build UI here
    CLAY({
        .id = CLAY_ID("OuterContainer"),
        .backgroundColor = COLOR_BG,
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = layoutExpand,
            .padding = CLAY_PADDING_ALL(16),
            .childGap = 16
        }
    }) {
        // Child elements
        CLAY({
            .id = CLAY_ID("TitleBar"),
            .layout = {
                .sizing = {
                    .height = CLAY_SIZING_FIXED(60),
                    .width = CLAY_SIZING_GROW(0)
                },
                .padding = {16,16,0,0},
                .childGap = 16,
                .childAlignment = {
                    .y = CLAY_ALIGN_Y_CENTER
                }
            },
            .backgroundColor = COLOR_ACCENT,
            .cornerRadius = CLAY_CORNER_RADIUS(8)
        }) {
            CLAY({
                .id = CLAY_ID("Header"),
            }){
                CLAY_TEXT(CLAY_STRING("Artifact Simulator for Genshin Impact"), CLAY_TEXT_CONFIG({
                    .fontId = FONT_ID_HONCHOKOMONO,
                    .fontSize = 24,
                    .textColor = COLOR_WHITE})
                );
            }
        }
        CLAY({
            .id = CLAY_ID("Inputs"),
            .layout = {
                .sizing = layoutExpand,
                .childGap = 16
            },
            .backgroundColor = COLOR_WHITE,
            .cornerRadius = CLAY_CORNER_RADIUS(8)
        }) {
            CLAY({ 
                .id = CLAY_ID("InputContent"),
                .clip = {
                    .vertical = true,
                    .childOffset = Clay_GetScrollOffset() },
                    .layout = {
                        .layoutDirection = CLAY_TOP_TO_BOTTOM,
                        .childGap = 16,
                        .padding = CLAY_PADDING_ALL(16),
                        .sizing = layoutExpand
                    }
                }) {
                    // put stuff here
                    CLAY({
                        .id = CLAY_ID("InputTitle"),
                    }){
                        CLAY_TEXT(CLAY_STRING("INPUTS"), CLAY_TEXT_CONFIG({
                            .fontId = FONT_ID_HONCHOKOMONO,
                            .fontSize = 24,
                            .textColor = COLOR_BLACK})
                        );
                    }
                }
            }


        CLAY({
            .id = CLAY_ID("Outputs"),
            .layout = {
                .sizing = layoutExpand,
                .childGap = 16
            },
            .backgroundColor = COLOR_WHITE,
            .cornerRadius = CLAY_CORNER_RADIUS(8)
        }) {
            CLAY({ 
                .id = CLAY_ID("OutputContent"),
                .clip = {
                    .vertical = true,
                    .childOffset = Clay_GetScrollOffset() },
                    .layout = {
                        .layoutDirection = CLAY_TOP_TO_BOTTOM,
                        .childGap = 16,
                        .padding = CLAY_PADDING_ALL(16),
                        .sizing = layoutExpand
                    }
                }) {
                    // put stuff here
                    CLAY({
                        .id = CLAY_ID("OutputTitle"),
                    }){
                        CLAY_TEXT(CLAY_STRING("OUTPUTS"), CLAY_TEXT_CONFIG({
                            .fontId = FONT_ID_HONCHOKOMONO,
                            .fontSize = 24,
                            .textColor = COLOR_BLACK})
                        );
                    }
                }
            }

        }

	Clay_RenderCommandArray renderCommands = Clay_EndLayout();
        return renderCommands;
    }
