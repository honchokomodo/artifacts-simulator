// vim: ts=2 sw=2
#include "components.c"
#include "raylib.h"
//#include "scenario.c"
//#include "artifact_ui.c"
//#include "character_ui.c"
//#include "weapon_ui.c"

Clay_RenderCommandArray create_layout(Interface_Data *data) {
	
	// Define images (prob better way to do this)
	Texture2D * yoimiya_img_tex = ic_get_tex("resources/images/characters/yoimiya_portrait.png");
	
	Clay_BeginLayout();
	
	// TODO: gradient overrides the background color or vice versa but I want both???
	CustomElement *gradient = la_alloc(&arena, sizeof(*gradient));
	gradient->type = CUSTOM_ELEMENT_TYPE_GRADIENT;
	gradient->customData.gradient = (CircleGradient) { .x1 = 950, .y1 = 100, .x2 = 100, .y2 = 668, .radius = 800, .start1 = {0xe6, 0xf8, 0xbd, 0xff}, .end1 = {0xe6, 0xf8, 0xbd, 0x00}, .start2 = {0xdb, 0xff, 0xdd, 0xff}, .end2 = {0xdb, 0xff, 0xdd, 0x00} };

	//Build UI here
	CLAY(CLAY_ID("Background_Container"), { .layout = { .sizing = layoutExpand }, .backgroundColor = {0xf8, 0xff, 0xe9, 0xff} }){
		CLAY(CLAY_ID("Bg_Gradient"), { .layout = { .sizing = layoutExpand, .childAlignment.x = CLAY_ALIGN_X_CENTER, .padding.top = 30 }, .custom = gradient }){
			CLAY(CLAY_ID("Main_Content_Container"), { .layout = { .sizing = {CLAY_SIZING_PERCENT(0.75), CLAY_SIZING_GROW(0)}, .layoutDirection = CLAY_TOP_TO_BOTTOM }, .backgroundColor = { 0xff, 0xff, 0xff, 0xff}, .cornerRadius = 32, }){
				CLAY(CLAY_ID("Top_Container"), { .layout = { .sizing = layoutWide }}){}
				CLAY(CLAY_ID("Bottom_Container"), {.layout = { .sizing = layoutExpand }}){}
			}
		}
	}

	Clay_RenderCommandArray renderCommands = Clay_EndLayout();

  for (int i = 0; i < renderCommands.length; i++) {
    Clay_RenderCommand *renderCommand = &renderCommands.internalArray[i];

    switch (renderCommand->commandType) {
      case CLAY_RENDER_COMMAND_TYPE_CUSTOM: 
				Clay_CustomRenderData *config = &renderCommand->renderData.custom;
				CustomElement *customElement = (CustomElement *)config-> customData;
			  if(!customElement) continue;
				switch(customElement->type) {
					case CUSTOM_ELEMENT_TYPE_GRADIENT: {
						CircleGradient gradientData = customElement->customData.gradient;	
						DrawCircleGradient(
							gradientData.x1, // centerX
							gradientData.y1, // centerY
							gradientData.radius, // radius
							gradientData.start1,
							gradientData.end1
						);
						DrawCircleGradient(
							gradientData.x2, // centerX
							gradientData.y2, // centerY
							gradientData.radius, // radius
							gradientData.start2,
							gradientData.end2
						);
						break;
					}
			 break;
			}
    }
  }
	return renderCommands;
}

