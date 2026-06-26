// main.c

enum BUTTON_ANCHOR { UL, UR, LL, LR };

// HEADERS
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// CONSTANTS
const int BannerFontSize = 32;
const int appFPS = 16;
const int windowBorder = 32;
const int buttonRectBorder = 32;

// APPSTATE
enum APPSTATE_ENUM { CLOSING, LOADING_APP, MAIN_MENU };
enum APPSTATE_ENUM APPSTATE = LOADING_APP;

// STRUCTURES
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

// STATIC STRUCT INSTANCES
struct BUTTON mainMenuExitButton = {	.x = 64,
					.y = 64,
					.w = 128,
					.h = 16,
					.defaultFillColor = {255,255,255,255},
					.pressedFillColor = {255,0,0,255},
					.fillColor = {255, 255, 255, 255},
					.textColor = {0, 0, 0, 255},
					.text = "EXIT APP",
					.textFontSize = 24,
					.pressed = false,
					.anchor = LR,
					.counter = 0,
					.wasPressed = false,
					.needsAppstate = MAIN_MENU
};

bool isMouseOverButton(struct BUTTON button) {
	// setup for calculations
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
	// boundary check
	int mousex = GetMouseX();
	int mousey = GetMouseY();
	if (mousex > x0 && mousex < x1 && mousey > y0 && mousey < y1) {
		return true;
	} else {
		return false;
	};
}

// just render button on screen, not make it clickable
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
		// mainMenuExitButton
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
					//APPSTATE = CLOSING;
					;
				};
				mainMenuExitButton.fillColor = mainMenuExitButton.defaultFillColor;
				strcpy(mainMenuExitButton.text, "EXIT APP");
			};
		};
}

// MISC
int loadingAppCounter = 0;

// DRAW A BANNER IN THE MIDDLE OF THE SCREEN
// TODO: make it semitransparent
void DrawBanner(char text[], int width, int height) {
	int posx = width / 2 - MeasureText(text, BannerFontSize) / 2;
	int posy = height / 2 - BannerFontSize / 2;
	DrawRectangle(posx - 20,
	posy - 10,
	MeasureText(text, BannerFontSize) + 40,
	BannerFontSize + 20,
	DARKGRAY);
	DrawText(text, posx, posy, BannerFontSize, WHITE);
}

int main(void) {
	// WINDOW SETUP
	printf("ENTERED MAIN\n");
	InitWindow(1, 1, "PATHAPP");
	SetTargetFPS(appFPS);
	const int width = GetMonitorWidth(0) - windowBorder;
	const int height = GetMonitorHeight(0) - windowBorder;
	printf("GetMonitorWidth(0)-windowBorder = %i\n", width);
	printf("GetMonitorHeight(0)-windowBorder = %i\n", height);
	SetWindowSize(width, height);
	// DRAWLOOP
	while (APPSTATE != CLOSING) {
		BeginDrawing();
		processButtons();
		if (APPSTATE == MAIN_MENU) {
			ClearBackground(DARKGRAY);
		};
		if (APPSTATE == LOADING_APP) {
			ClearBackground(BLACK);
			DrawBanner("LOADING, PLEASE WAIT", width, height);
			if (loadingAppCounter >= appFPS * .25) {
				APPSTATE = MAIN_MENU;
			};
			loadingAppCounter += 1;
			printf("loadingAppCounter = %i\n", loadingAppCounter);
		};
		EndDrawing();
		if (WindowShouldClose()) {APPSTATE = CLOSING;};
	};
	// CLEANUP ON EXIT
	CloseWindow();
	return 0;
}
