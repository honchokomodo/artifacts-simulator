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

	// Custom Renderer Elements	
	CustomElement *gradient = la_alloc(&arena, sizeof(*gradient));
	gradient->type = CUSTOM_ELEMENT_TYPE_GRADIENT;
	gradient->customData.gradient = (CircleGradient) { .radius = 500, .start1 = {0xe6, 0xf8, 0xbd, 0xff}, .end1 = {0xe6, 0xf8, 0xbd, 0x00}, .start2 = {0xdb, 0xff, 0xdd, 0xff}, .end2 = {0xdb, 0xff, 0xdd, 0x00} };

	//Build UI here
	CLAY(CLAY_ID("Background_Container"), { .layout = { .sizing = layoutExpand, .childAlignment.x = CLAY_ALIGN_X_CENTER, .padding.top = 30 }, .custom=gradient }){
		CLAY(CLAY_ID("Main_Content_Container"), { .layout = { .sizing = {CLAY_SIZING_PERCENT(0.70), CLAY_SIZING_GROW(0)}, .layoutDirection = CLAY_TOP_TO_BOTTOM }, .backgroundColor = { 0xff, 0xff, 0xff, 0xff}, .cornerRadius = 32, }){
			CLAY(CLAY_ID("Top_Container"), { .layout = { .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(110)}, .layoutDirection = CLAY_LEFT_TO_RIGHT }}){
				CLAY(CLAY_ID_LOCAL("Char"), { .layout = { .sizing = layoutPercentHoriz(0.333) }, .backgroundColor = {0x00, 0x00, 0x00, 0x8f}, .border = { .width = 1, .color = {0xff, 0xff, 0xff, 0xff} } }){
					// TODO: Pass through character name
					text_p(ch2str("[Character_Name]"));
				}
				CLAY(CLAY_ID_LOCAL("Weapon"), { .layout = { .sizing = layoutPercentHoriz(0.333) }, .backgroundColor = {0x00, 0x00, 0x00, 0x8f}, .border = { .width = 1, .color = {0xff, 0xff, 0xff, 0xff} } }){
					// TODO: Pass through weapon name
					text_p(ch2str("[Weapon_Name]"));
				}
				CLAY(CLAY_ID_LOCAL("Info"), { .layout = { .sizing = layoutPercentHoriz(0.333) }, .backgroundColor = {0x00, 0x00, 0x00, 0x8f},.border = { .width = 1, .color = {0xff, 0xff, 0xff, 0xff} } }){
					// TODO: Buttons to external links (Socials!)
					text_p(ch2str("[Links]"));
				}
			}

			CLAY(CLAY_ID("Bottom_Container"), {.layout = { .sizing = layoutExpand }}){}
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
						Color bg = (Color) {0xf8, 0xff, 0xe9, 0xff};
						float w = data->windowSize.width;
						float h = data->windowSize.height;
						DrawRectangle(0, 0, w, h, bg);
						DrawCircleGradient( w-200, 350, gradientData.radius, gradientData.start1, gradientData.end1 );
						DrawCircleGradient( 200, h-350, gradientData.radius, gradientData.start2, gradientData.end2);
						break;
					}
			 break;
			}
    }
  }
	return renderCommands;
}

