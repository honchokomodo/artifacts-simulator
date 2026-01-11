void dropdown_button(Clay_ElementId id, Clay_ElementId menu_id, Clay_String button_text, Clay_String items_text[], size_t items_text_len, bool state){

	CLAY({
		.id = id,
		.layout = {
			.padding = {4,4,4,4},
		},
		.backgroundColor = COLOR_BUTTON,
		.cornerRadius = CLAY_CORNER_RADIUS(8),
	}){
		text_p(button_text);

		if(state){
			dropdown_menu(menu_id, items_text, items_text_len);	
		}
	}
}

static void dropdown_menu(Clay_ElementId menu_id, Clay_String items_text[], size_t items_text_len){

	CLAY({
		.id = menu_id,
		.floating = {
			.attachTo = CLAY_ATTACH_TO_PARENT,
			.attachPoints = {
				.parent = CLAY_ATTACH_POINT_CENTER_BOTTOM,
				.element = CLAY_ATTACH_POINT_CENTER_TOP
			},
		}
	}){
		CLAY({
			.layout = {
				.layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing.width = CLAY_SIZING_FIXED(135),
			},
			.cornerRadius = CLAY_CORNER_RADIUS(8)
		}) {
			for(int i=0; i < items_text_len; i++ ){

				Clay_CornerRadius cornerRadius;
				Clay_Color bg_color;
		
				if (i == 0) {
					cornerRadius = (Clay_CornerRadius){4, 4, 0, 0};
				} else if (i == items_text_len - 1) {
					cornerRadius = (Clay_CornerRadius){0, 0, 4, 4};
				} else {
					cornerRadius = (Clay_CornerRadius){0, 0, 0, 0};
				}

				if ( !(i % 2) ) { 
					bg_color = (Clay_Color) { 0xf8, 0xf8, 0xd4, 0xff };
				} else {
					bg_color = (Clay_Color) { 0xd2, 0xb2, 0x78, 0xff };
				}
	
				CLAY({
					.id = CLAY_SIDI(menu_id.stringId, i),
					.layout = {
						.padding = {4,4,2,2},
						.sizing = {
							.width = CLAY_SIZING_PERCENT(1)
						}
					},
					.backgroundColor = bg_color,
				}){
					COLOR_TEXT = (Clay_Color) { 0x16, 0x15, 0x29, 0xff };
					text_p(items_text[i]);
					COLOR_TEXT = (Clay_Color) { 0xff, 0xff, 0xff, 0xff };
				}
			}
		}
	}

}