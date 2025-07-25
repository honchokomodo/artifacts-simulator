#include <clay.h>
#include <stdint.h>
#include <stdlib.h>

const int FONT_ID_BODY_16 = 0;
const int FONT_ID_H1_24 = 1;
Clay_Color COLOR_WHITE = { 255, 255, 255, 255};
Clay_Color COLOR_ACCENT = {255, 95, 207, 255};
Clay_Color COLOR_BG = {255, 210, 230, 255};
Clay_Color COLOR_BLACK = { 0, 0, 0, 255};

typedef struct {
    Clay_String title;
    Clay_String contents;
} Document;

typedef struct {
    Document *documents;
    uint32_t length;
} DocumentArray;

Document documentsRaw[3];
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
    documents.documents[0] = (Document){ .title = CLAY_STRING("Artifact Simulator for Genshin Impact") };
    documents.documents[1] = (Document){ .title = CLAY_STRING("INPUTS")};
    documents.documents[2] = (Document){ .title = CLAY_STRING("OUTPUTS")};

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
                Document selectedDocument = documents.documents[0];
                CLAY_TEXT(selectedDocument.title, CLAY_TEXT_CONFIG({
                    .fontId = FONT_ID_H1_24,
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
                        Document selectedDocument = documents.documents[1];
                        CLAY_TEXT(selectedDocument.title, CLAY_TEXT_CONFIG({
                            .fontId = FONT_ID_H1_24,
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
                        Document selectedDocument = documents.documents[2];
                        CLAY_TEXT(selectedDocument.title, CLAY_TEXT_CONFIG({
                            .fontId = FONT_ID_H1_24,
                            .fontSize = 24,
                            .textColor = COLOR_BLACK})
                        );
                    }
                }
            }

        }
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();
        for (int32_t i = 0; i < renderCommands.length; i++) {
            Clay_RenderCommandArray_Get(&renderCommands, i)->boundingBox.y += data->yOffset;
        }
        return renderCommands;
    }