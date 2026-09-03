int width = 0;
int height = 0;
const int buttonRectBorder = 8;
int FastRunSettingsButtonAppearCounter = 0;

struct BUTTON {
	int x;
	int y;
	int w;
	int h;
	Color defaultFillColor;
	Color pressedFillColor;
	Color fillColor;
	Color textColor;
	char text[64];
	int textFontSize;
	bool pressed;
	enum BUTTON_ANCHOR anchor;
	int counter;
	bool wasPressed;
	enum APPSTATE_ENUM needsAppstate;
};


bool isMouseOverButton(struct BUTTON button) {
	int x0 = 0;
	int y0 = 0;
	int x1 = 0;
	int y1 = 0;
	if (button.anchor == UL) {
		x0 = button.x - buttonRectBorder;
		y0 = button.y - buttonRectBorder;
		x1 = button.x + button.w + buttonRectBorder;
		y1 = button.y + button.h + buttonRectBorder;
	} else if (button.anchor == UR) {
		x0 = GetScreenWidth() - button.x - button.w - buttonRectBorder;
		y0 = button.y - buttonRectBorder;
		x1 = x0 + button.w + buttonRectBorder * 2;
		y1 = button.y + button.h + buttonRectBorder;
	} else if (button.anchor == LL) {
		x0 = button.x - buttonRectBorder;
		y0 = GetScreenHeight() - button.y - button.h - buttonRectBorder;
		x1 = button.x + button.w + buttonRectBorder;
		y1 = y0 + button.h + buttonRectBorder * 2;
	} else if (button.anchor == LR) {
		x0 = GetScreenWidth() - button.x - button.w - buttonRectBorder;
		y0 = GetScreenHeight() - button.y - button.h - buttonRectBorder;
		x1 = x0 + button.w + buttonRectBorder * 2;
		y1 = y0 + button.h + buttonRectBorder * 2;
	};
	int mousex = GetMouseX();
	int mousey = GetMouseY();
	if (mousex > x0 && mousex < x1 && mousey > y0 && mousey < y1) {
		return true;
	} else {
		return false;
	};
}

void renderButton(struct BUTTON button) {
	if (button.anchor == UL) {
		DrawRectangle(button.x - buttonRectBorder, button.y - buttonRectBorder,
		button.w + buttonRectBorder * 2,
		button.h + buttonRectBorder * 2, button.fillColor);
		int textposx = (button.x + (button.w / 2)) -
		MeasureText(button.text, button.textFontSize) / 2;
		int textposy = (button.y + (button.h / 2)) - button.textFontSize / 2;
		DrawText(button.text, textposx, textposy, button.textFontSize,
		button.textColor);
	};
	if (button.anchor == UR) {
		DrawRectangle(GetScreenWidth() - button.x - button.w - buttonRectBorder,
		button.y - buttonRectBorder, button.w + buttonRectBorder * 2,
		button.h + buttonRectBorder * 2, button.fillColor);
		int textposx = (button.x + (button.w / 2)) -
		MeasureText(button.text, button.textFontSize) / 2;
		int textposy = (button.y + (button.h / 2)) - button.textFontSize / 2;
		DrawText(button.text,
		GetScreenWidth() - textposx -
		MeasureText(button.text, button.textFontSize),
		textposy, button.textFontSize, button.textColor);
	};
	if (button.anchor == LL) {
		DrawRectangle(button.x - buttonRectBorder,
		GetScreenHeight() - button.y - button.h - buttonRectBorder,
		button.w + buttonRectBorder * 2,
		button.h + buttonRectBorder * 2, button.fillColor);
		int textposx = (button.x + (button.w / 2)) -
		MeasureText(button.text, button.textFontSize) / 2;
		int textposy = (button.y + (button.h / 2)) - button.textFontSize / 2;
		DrawText(button.text, textposx,
		GetScreenHeight() - textposy - button.textFontSize,
		button.textFontSize, button.textColor);
	};
	if (button.anchor == LR) {
		DrawRectangle(GetScreenWidth() - button.x - button.w - buttonRectBorder,
		GetScreenHeight() - button.y - button.h - buttonRectBorder,
		button.w + buttonRectBorder * 2,
		button.h + buttonRectBorder * 2, button.fillColor);
		int textposx = (button.x + (button.w / 2)) -
		MeasureText(button.text, button.textFontSize) / 2;
		int textposy = (button.y + (button.h / 2)) - button.textFontSize / 2;
		DrawText(button.text,
		GetScreenWidth() - textposx -
		MeasureText(button.text, button.textFontSize),
		GetScreenHeight() - textposy - button.textFontSize,
		button.textFontSize, button.textColor);
	};
}

bool isButtonPressed(struct BUTTON button) {
	if (IsMouseButtonPressed(0) && isMouseOverButton(button)) {
		return true;
	} else {
		return false;
	};
}

void processSettingsScreenUpperText(void) {
	DrawText("SETTINGS", 20, 20, 32, WHITE);
	DrawText(TextFormat("Current window width - %i",width), 20, 80, 24, WHITE);
	DrawText(TextFormat("Current window height - %i",height), 20, 110, 24, WHITE);
}

void processSettingsScreenFastRunButton(void) {
	static struct BUTTON FastRunSettingsButton = {			.x = 20,
									.y = 20,
									.w = 128,
									.h = 16,
									.defaultFillColor = { 127, 127, 127, 255 },
									.pressedFillColor = { 187, 187, 187, 255 } ,
									.fillColor = { 127, 127, 127, 255 },
									.textColor = { 85, 85, 85, 255 },
									.text = "FAST RUN",
									.textFontSize = 16,
									.pressed = false,
									.anchor = LL,
									.counter = 0,
									.wasPressed = false,
									.needsAppstate = SETTINGS_SCREEN
	};
	renderButton(FastRunSettingsButton);
	if (isButtonPressed(FastRunSettingsButton)) {
		FastRunSettingsButton.fillColor = FastRunSettingsButton.pressedFillColor;
		FastRunSettingsButton.counter = 0;
		FastRunSettingsButton.wasPressed = true;
	};
	FastRunSettingsButton.counter += 1;
	if (FastRunSettingsButton.counter > appFPS/2) {
		if (FastRunSettingsButton.wasPressed==true) {
			FastRunSettingsButton.wasPressed = false;
			playerFastRun = true;
		};
		FastRunSettingsButton.fillColor = FastRunSettingsButton.defaultFillColor;
	};
		if (playerFastRun) {
			DrawText("ON",170,height-39,24,WHITE);
		};
}

void processSettingsScreenSensivityControls(void) {
	static struct BUTTON SensivityUpSettingsButton = {		.x = 128,
									.y = 80,
									.w = 20,
									.h = 16,
									.defaultFillColor = { 127, 127, 127, 255 },
									.pressedFillColor = { 187, 187, 187, 255 } ,
									.fillColor = { 127, 127, 127, 255 },
									.textColor = { 85, 85, 85, 255 },
									.text = "+",
									.textFontSize = 24,
									.pressed = false,
									.anchor = LL,
									.counter = 0,
									.wasPressed = false,
									.needsAppstate = SETTINGS_SCREEN
	};
	static struct BUTTON SensivityDownSettingsButton = {		.x = 20,
									.y = 80,
									.w = 20,
									.h = 16,
									.defaultFillColor = { 127, 127, 127, 255 },
									.pressedFillColor = { 187, 187, 187, 255 } ,
									.fillColor = { 127, 127, 127, 255 },
									.textColor = { 85, 85, 85, 255 },
									.text = "-",
									.textFontSize = 24,
									.pressed = false,
									.anchor = LL,
									.counter = 0,
									.wasPressed = false,
									.needsAppstate = SETTINGS_SCREEN
	};
	static struct BUTTON SensivitySettingsDisplayButton = {		.x = 60,
									.y = 80,
									.w = 48,
									.h = 16,
									.defaultFillColor = { 127, 127, 127, 255 },
									.pressedFillColor = { 187, 187, 187, 255 } ,
									.fillColor = { 127, 127, 127, 255 },
									.textColor = { 85, 85, 85, 255 },
									.text = "100%",
									.textFontSize = 16,
									.pressed = false,
									.anchor = LL,
									.counter = 0,
									.wasPressed = false,
									.needsAppstate = SETTINGS_SCREEN
	};
	renderButton(SensivityDownSettingsButton);
	if (isButtonPressed(SensivityDownSettingsButton)) {
		SensivityDownSettingsButton.fillColor = SensivityDownSettingsButton.pressedFillColor;
		SensivityDownSettingsButton.counter = 0;
		SensivityDownSettingsButton.wasPressed = true;
	}
	SensivityDownSettingsButton.counter += 1;
	if (SensivityDownSettingsButton.counter > appFPS/16) {
		if (SensivityDownSettingsButton.wasPressed==true) {
			SensivityDownSettingsButton.wasPressed = false;
			ViewSensivity -= 0.05;
		};
		SensivityDownSettingsButton.fillColor = SensivityDownSettingsButton.defaultFillColor;
	};
	renderButton(SensivityUpSettingsButton);
	if (isButtonPressed(SensivityUpSettingsButton)) {
		SensivityUpSettingsButton.fillColor = SensivityUpSettingsButton.pressedFillColor;
		SensivityUpSettingsButton.counter = 0;
		SensivityUpSettingsButton.wasPressed = true;
	}
	SensivityUpSettingsButton.counter += 1;
	if (SensivityUpSettingsButton.counter > appFPS/16) {
		if (SensivityUpSettingsButton.wasPressed==true) {
			SensivityUpSettingsButton.wasPressed = false;
			ViewSensivity += 0.05;
		};
		SensivityUpSettingsButton.fillColor = SensivityUpSettingsButton.defaultFillColor;
	};
	renderButton(SensivitySettingsDisplayButton);
	TextCopy(SensivitySettingsDisplayButton.text,TextFormat("%.0f%%",ViewSensivity*100));
	if (isButtonPressed(SensivitySettingsDisplayButton)) {
		SensivitySettingsDisplayButton.fillColor = SensivitySettingsDisplayButton.pressedFillColor;
		SensivitySettingsDisplayButton.counter = 0;
		SensivitySettingsDisplayButton.wasPressed = true;
	}
	SensivitySettingsDisplayButton.counter += 1;
	if (SensivitySettingsDisplayButton.counter > appFPS/16) {
		if (SensivitySettingsDisplayButton.wasPressed==true) {
			SensivitySettingsDisplayButton.wasPressed = false;
			ViewSensivity = 0.50;
		};
		SensivitySettingsDisplayButton.fillColor = SensivitySettingsDisplayButton.defaultFillColor;
	};
	int textposx = (SensivityUpSettingsButton.x + (SensivityUpSettingsButton.w / 2)) -
	MeasureText(SensivityUpSettingsButton.text, SensivityUpSettingsButton.textFontSize) / 2;
	int textposy = (SensivityUpSettingsButton.y + (SensivityUpSettingsButton.h / 2)) -
	SensivityUpSettingsButton.textFontSize / 2;
	DrawText(
		"SENSIVITY", textposx+40,
		GetScreenHeight() - textposy+2 - SensivityUpSettingsButton.textFontSize,
		SensivityUpSettingsButton.textFontSize, WHITE
	);
}

void processSettingsScreenButtons(void) {
	processSettingsScreenUpperText();
	processSettingsScreenFastRunButton();
	processSettingsScreenSensivityControls();
}

void processMainMenuExitButton(void) {
	static struct BUTTON mainMenuExitButton = {			.x = 64,
									.y = 64,
									.w = 128,
									.h = 16,
									.defaultFillColor = {255,255,255,255},
									.pressedFillColor = {255,0,0,255},
									.fillColor = {255, 255, 255, 255},
									.textColor = {0, 0, 0, 255},
									.text = "EXIT",
									.textFontSize = 24,
									.pressed = false,
									.anchor = LR,
									.counter = 0,
									.wasPressed = false,
									.needsAppstate = MAIN_MENU
	};
	renderButton(mainMenuExitButton);
	if (isButtonPressed(mainMenuExitButton)) {
		mainMenuExitButton.fillColor = mainMenuExitButton.pressedFillColor;
		strcpy(mainMenuExitButton.text, "GOODBYE");
		mainMenuExitButton.counter = 0;
		mainMenuExitButton.wasPressed = true;
	};
	mainMenuExitButton.counter += 1;
	if (mainMenuExitButton.counter > appFPS/4) {
		if (mainMenuExitButton.wasPressed==true) {
			mainMenuExitButton.wasPressed = false;
			APPSTATE = CLOSING;
		};
		mainMenuExitButton.fillColor = mainMenuExitButton.defaultFillColor;
		strcpy(mainMenuExitButton.text, "EXIT");
	};
}

void processMainMenuPlanetButton(void) {
	static struct BUTTON planetButton = {				.x = 16,
									.y = 16,
									.w = 16,
									.h = 16,
									.defaultFillColor = { 85, 85, 85, 255 },
									.pressedFillColor = { 255, 255, 255, 255 } ,
									.fillColor = { 85, 85, 85, 255 },
									.textColor = { 85, 85, 85, 255 },
									.text = "",
									.textFontSize = 4,
									.pressed = false,
									.anchor = LL,
									.counter = 0,
									.wasPressed = false,
									.needsAppstate = MAIN_MENU
	};
	renderButton(planetButton);
	if (isButtonPressed(planetButton)) {
		planetButton.fillColor = planetButton.pressedFillColor;
		planetButton.counter = 0;
		planetButton.wasPressed = true;
	}
	planetButton.counter += 1;
	if (planetButton.counter > appFPS/2) {
		if (planetButton.wasPressed==true) {
			planetButton.wasPressed = false;
			APPSTATE = PLANET;
			;
		};
		planetButton.fillColor = planetButton.defaultFillColor;
	};
}

void processMainMenuBallButton(void) {
	static struct BUTTON mainMenuBallButton = {			.x = 16,
									.y = 16,
									.w = 128,
									.h = 16,
									.defaultFillColor = { 127, 127, 127, 255 },
									.pressedFillColor = { 187, 187, 187, 255 } ,
									.fillColor = { 127, 127, 127, 255 },
									.textColor = { 85, 85, 85, 255 },
									.text = "BALL",
									.textFontSize = 16,
									.pressed = false,
									.anchor = UL,
									.counter = 0,
									.wasPressed = false,
									.needsAppstate = MAIN_MENU
	};
	renderButton(mainMenuBallButton);
	if (isButtonPressed(mainMenuBallButton)) {
		mainMenuBallButton.fillColor = mainMenuBallButton.pressedFillColor;
		mainMenuBallButton.counter = 0;
		mainMenuBallButton.wasPressed = true;
	}
	mainMenuBallButton.counter += 1;
	if (mainMenuBallButton.counter > appFPS/4) {
		if (mainMenuBallButton.wasPressed==true) {
			mainMenuBallButton.wasPressed = false;
			APPSTATE = PHYSICS_TEST;
		};
		mainMenuBallButton.fillColor = mainMenuBallButton.defaultFillColor;
	};
}

void processMainMenuPathgameButton(void) {
	static struct BUTTON mainMenuPathgameButton = {			.x = 16,
									.y = 64,
									.w = 128,
									.h = 16,
									.defaultFillColor = { 127, 127, 127, 255 },
									.pressedFillColor = { 187, 187, 187, 255 } ,
									.fillColor = { 127, 127, 127, 255 },
									.textColor = { 85, 85, 85, 255 },
									.text = "pathgame wip",
									.textFontSize = 16,
									.pressed = false,
									.anchor = UL,
									.counter = 0,
									.wasPressed = false,
									.needsAppstate = MAIN_MENU
	};
	renderButton(mainMenuPathgameButton);
	if (isButtonPressed(mainMenuPathgameButton)) {
		mainMenuPathgameButton.fillColor = mainMenuPathgameButton.pressedFillColor;
		mainMenuPathgameButton.counter = 0;
		mainMenuPathgameButton.wasPressed = true;
	}
	mainMenuPathgameButton.counter += 1;
	if (mainMenuPathgameButton.counter > appFPS/4) {
		if (mainMenuPathgameButton.wasPressed==true) {
			mainMenuPathgameButton.wasPressed = false;
			APPSTATE = PATHGAME;
			;
		};
		mainMenuPathgameButton.fillColor = mainMenuPathgameButton.defaultFillColor;
	};
}

void processMainMenuSettingsButton(void) {
	static struct BUTTON SettingsButton = {				.x = 16,
									.y = 16,
									.w = 128,
									.h = 16,
									.defaultFillColor = { 127, 127, 127, 255 },
									.pressedFillColor = { 187, 187, 187, 255 } ,
									.fillColor = { 127, 127, 127, 255 },
									.textColor = { 85, 85, 85, 255 },
									.text = "SETTINGS",
									.textFontSize = 16,
									.pressed = false,
									.anchor = UR,
									.counter = 0,
									.wasPressed = false,
									.needsAppstate = MAIN_MENU
	};
	renderButton(SettingsButton);
	if (isButtonPressed(SettingsButton)) {
		SettingsButton.fillColor = SettingsButton.pressedFillColor;
		SettingsButton.counter = 0;
		SettingsButton.wasPressed = true;
	}
	SettingsButton.counter += 1;
	if (SettingsButton.counter > appFPS/4) {
		if (SettingsButton.wasPressed==true) {
			FastRunSettingsButtonAppearCounter = 0;
			SettingsButton.wasPressed = false;
			APPSTATE = SETTINGS_SCREEN;
			;
		};
		SettingsButton.fillColor = SettingsButton.defaultFillColor;
	};
}

void processMainMenuButtons(void) {
	processMainMenuExitButton();
	processMainMenuPlanetButton();
	processMainMenuBallButton();
	processMainMenuPathgameButton();
	processMainMenuSettingsButton();
}
