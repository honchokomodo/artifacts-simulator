#include <clay.h>
#include <stdint.h>
#include <stdlib.h>

const int FONT_ID_BODY_16 = 0;
const int FONT_ID_H1_24 = 1;
Clay_Color COLOR_WHITE = { 255, 255, 255, 255};
Clay_Color COLOR_PINK = {255, 95, 207, 255};
Clay_Color COLOR_LIGHT_PINK = {255, 206, 240, 255};
Clay_Color COLOR_LIGHT_PINK_1 = { 255, 215, 243, 255};
Clay_Color COLOR_LIGHTER_PINK = {255, 239, 247, 255};
Clay_Color COLOR_BLACK = { 0, 0, 0, 255};

typedef struct {
    Clay_String title;
    Clay_String contents;
} Document;

typedef struct {
    Document *documents;
    uint32_t length;
} DocumentArray;

Document documentsRaw[5];
DocumentArray documents = {
    .length = 5,
    .documents = documentsRaw
};

typedef struct {
    intptr_t offset;
    intptr_t memory;
} Interface_Arena;

typedef struct {
    int32_t selectedDocumentIndex;
    float yOffset;
    Interface_Arena frameArena;
} Interface_Data;

Interface_Data uiData_Initialize() {
    documents.documents[0] = (Document){ .title = CLAY_STRING("Artifact Simulator for Genshin Impact"), .contents = CLAY_STRING("An aritfact simulator for Genshin Impact.") };

    Interface_Data data = {
        .frameArena = { .memory = (intptr_t)malloc(1024) }
    };
    return data;
}

Clay_RenderCommandArray Artifact_CreateLayout(Interface_Data *data) {
    data->frameArena.offset = 0;

    Clay_BeginLayout();

    Clay_Sizing layoutExpand = {
        .width = CLAY_SIZING_GROW(0),
        .height = CLAY_SIZING_GROW(0)
    };

    //Build UI here
    CLAY({
        .id = CLAY_ID("OuterContainer"),
        .backgroundColor = COLOR_LIGHT_PINK,
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
            .backgroundColor = COLOR_PINK,
            .cornerRadius = CLAY_CORNER_RADIUS(8)
        }) {
            // Header buttons but we don't have any
            CLAY({
                .id = CLAY_ID("Header Title"),
            }){
                Document selectedDocument = documents.documents[data->selectedDocumentIndex];
                CLAY_TEXT(selectedDocument.title, CLAY_TEXT_CONFIG({
                    .fontId = FONT_ID_H1_24,
                    .fontSize = 24,
                    .textColor = COLOR_WHITE})
                );
            }
        }

        CLAY({
            .id = CLAY_ID("LowerContent"),
            .layout = {
                .sizing = layoutExpand,
                .childGap = 16
            },
            .backgroundColor = COLOR_PINK,
        }) {
            // There could be a sidebar here if we need it
            CLAY({ 
                .id = CLAY_ID("MainContent"),
                .backgroundColor = COLOR_LIGHTER_PINK,
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
                    // Document selectedDocument = documents.documents[data->selectedDocumentIndex];
                    // CLAY_TEXT(selectedDocument.title, CLAY_TEXT_CONFIG({
                    //     .fontId = FONT_ID_BODY_16,
                    //     .fontSize = 24,
                    //     .textColor = COLOR_BLACK })
                    // );
                    // CLAY_TEXT(selectedDocument.contents, CLAY_TEXT_CONFIG({
                    //     .fontId = FONT_ID_BODY_16,
                    //     .fontSize = 16,
                    //     .textColor = COLOR_BLACK })
                    // );
                }
            }
        }
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();
        for (int32_t i = 0; i < renderCommands.length; i++) {
            Clay_RenderCommandArray_Get(&renderCommands, i)->boundingBox.y += data->yOffset;
        }
        return renderCommands;
    }