// vim: ts=2 sw=2
#include "components.c"
#include "raylib.h"
//#include "scenario.c"
//#include "artifact_ui.c"
//#include "character_ui.c"
//#include "weapon_ui.c"

typedef struct {
	Color inner;
	Color outer;
} CircleGradient;

Clay_RenderCommandArray create_layout(Interface_Data *data) {
	
	// Define images (prob better way to do this)
	Texture2D * yoimiya_img_tex = ic_get_tex("resources/images/characters/yoimiya_portrait.png");
	
	Clay_BeginLayout();

	//Build UI here
	
	CLAY(CLAY_ID("Background_Container"),{ .layout = { .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)}, .childAlignment = {.x = CLAY_ALIGN_X_CENTER}, .padding.top = 30 }, .backgroundColor = { 0xf8, 0xff, 0xe9, 0xff } }){
		// DrawCircleGradient(100, 100, 100, (Color) {0xe6, 0xf8, 0xbd, 0xff}, (Color) {0xe6, 0xf8, 0xbd, 0x00});   
		CLAY(CLAY_ID("Main_Content_Container"),
		{
			.layout = { 
				.sizing = {CLAY_SIZING_PERCENT(0.75), CLAY_SIZING_GROW(0)},
				.layoutDirection = CLAY_TOP_TO_BOTTOM
			}, 
			.backgroundColor = { 0xff, 0xff, 0xff, 0xff},
			.cornerRadius = 32
		}){
			CLAY(CLAY_ID("Top_Container"), { .layout = { .sizing = {layoutWide} }}){

			}
			CLAY(CLAY_ID("Bottom_Container"), {.layout = { .sizing = {layoutExpand} }}){}
		}
	}
	
	Clay_RenderCommandArray renderCommands = Clay_EndLayout();
	return renderCommands;
}

