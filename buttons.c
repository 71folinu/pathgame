const int buttonRectBorder = 8;

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

struct BUTTON mainMenuExitButton = {	.x = 64,
					.y = 64,
					.w = 128,
					.h = 16,
					.defaultFillColor = {255,255,255,255},
					.pressedFillColor = {255,0,0,255},
					.fillColor = {255, 255, 255, 255},
					.textColor = {0, 0, 0, 255},
					.text = "exit app",
					.textFontSize = 24,
					.pressed = false,
					.anchor = LR,
					.counter = 0,
					.wasPressed = false,
					.needsAppstate = MAIN_MENU
};
struct BUTTON planetButton = {		.x = 16,
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

struct BUTTON physicsTestButton = {	.x = 16,
					.y = 16,
					.w = 128,
					.h = 16,
					.defaultFillColor = { 127, 127, 127, 255 },
					.pressedFillColor = { 187, 187, 187, 255 } ,
					.fillColor = { 127, 127, 127, 255 },
					.textColor = { 85, 85, 85, 255 },
					.text = "physics test",
					.textFontSize = 16,
					.pressed = false,
					.anchor = UL,
					.counter = 0,
					.wasPressed = false,
					.needsAppstate = MAIN_MENU
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

void processButtons(void) {
		if (APPSTATE == mainMenuExitButton.needsAppstate) {
			renderButton(mainMenuExitButton);
			if (isButtonPressed(mainMenuExitButton)) {
				mainMenuExitButton.fillColor = mainMenuExitButton.pressedFillColor;
				strcpy(mainMenuExitButton.text, "FUCK YOU");
				mainMenuExitButton.counter = 0;
				mainMenuExitButton.wasPressed = true;
			};
			mainMenuExitButton.counter += 1;
			if (mainMenuExitButton.counter > appFPS/2) {
				if (mainMenuExitButton.wasPressed==true) {
					mainMenuExitButton.wasPressed = false;
					APPSTATE = CLOSING;
				};
				mainMenuExitButton.fillColor = mainMenuExitButton.defaultFillColor;
				strcpy(mainMenuExitButton.text, "exit app");
			};
		};
		if (APPSTATE == planetButton.needsAppstate) {
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
		};
		if (APPSTATE == physicsTestButton.needsAppstate) {
			renderButton(physicsTestButton);
			if (isButtonPressed(physicsTestButton)) {
				physicsTestButton.fillColor = physicsTestButton.pressedFillColor;
				physicsTestButton.counter = 0;
				physicsTestButton.wasPressed = true;
			}
			physicsTestButton.counter += 1;
			if (physicsTestButton.counter > appFPS/2) {
				if (physicsTestButton.wasPressed==true) {
					physicsTestButton.wasPressed = false;
					APPSTATE = PHYSICS_TEST;
					;
				};
				physicsTestButton.fillColor = physicsTestButton.defaultFillColor;
			};
		};
}
