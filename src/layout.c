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

	// TODO: don't know what to do with memory allocation :(
	size_t temp = 256;
	la_Arena temp_arena = { .buf = malloc(temp), .bufsz = temp };
	CustomElement *gradient = la_alloc(&temp_arena, temp_arena.bufsz);
	gradient->type = CUSTOM_ELEMENT_TYPE_GRADIENT;
	gradient->customData.gradient = (CircleGradient) { .centerX = 100, .centerY = 100, .radius = 100, .start = {0xe6, 0xf8, 0xbd, 0xff}, .end = {0xe6, 0xf8, 0xbd, 0x00} };

	//Build UI here	
	CLAY(CLAY_ID("Background_Container"),{ .layout = { .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)}, .childAlignment = {.x = CLAY_ALIGN_X_CENTER}, .padding.top = 30 }, .backgroundColor = { 0xf8, 0xff, 0xe9, 0xff }, .custom=gradient }){
		// DrawCircleGradient(100, 100, 100, (Color) {0xe6, 0xf8, 0xbd, 0xff}, (Color) {0xe6, 0xf8, 0xbd, 0x00});  
		CLAY(CLAY_ID("Main_Content_Container"),
		{
			.layout = { 
				.sizing = {CLAY_SIZING_PERCENT(0.75), CLAY_SIZING_GROW(0)},
				.layoutDirection = CLAY_TOP_TO_BOTTOM
			}, 
			.backgroundColor = { 0xff, 0xff, 0xff, 0xff},
			.cornerRadius = 32,
			.custom = gradient,
		}){
			CLAY(CLAY_ID("Top_Container"), { .layout = { .sizing = layoutWide }}){

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
						DrawCircleGradient(
							gradientData.centerX, // centerX
							gradientData.centerY, // centerY
							gradientData.radius, // radius
							gradientData.start,
							gradientData.end
						);
						break;
					}
			 break;
			}
    }
  }
	return renderCommands;
	la_reset(&temp_arena);
	free(temp_arena.buf);
}

