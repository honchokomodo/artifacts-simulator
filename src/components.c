const int FONT_ID_HONCHOKOMONO = 0;
Clay_Color COLOR_WHITE = { 255, 255, 255, 255};
Clay_Color COLOR_ACCENT = {255, 95, 207, 255};
Clay_Color COLOR_BG = {255, 210, 230, 255};
Clay_Color COLOR_BLACK = { 0, 0, 0, 255};


void text_large(Clay_String text, Clay_Color color){
	CLAY({
	}){
		CLAY_TEXT(text,
			CLAY_TEXT_CONFIG({
				.fontId = FONT_ID_HONCHOKOMONO,
				.fontSize = 24,
				.textColor = color
			})
		);
	}
}
