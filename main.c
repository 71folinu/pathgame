// main.c

enum BUTTON_ANCHOR { UL, UR, LL, LR };

// HEADERS
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// CONSTANTS
const int BannerFontSize = 32;
const int appFPS = 32;
const int windowBorder = 32;
const int buttonRectBorder = 8;

// APPSTATE
enum APPSTATE_ENUM { CLOSING, LOADING_APP, MAIN_MENU, PLANET };
//enum APPSTATE_ENUM APPSTATE = LOADING_APP;
enum APPSTATE_ENUM APPSTATE = PLANET;

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
					// APPSTATE = CLOSING;
					;
				};
				mainMenuExitButton.fillColor = mainMenuExitButton.defaultFillColor;
				strcpy(mainMenuExitButton.text, "exit app");
			};
		};
		// planetButton
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
					APPSTATE = PLANET;
					;
				};
				planetButton.fillColor = planetButton.defaultFillColor;
			};
		};
}

// GLOBAL VARS
int loadingAppCounter = 0;
int clickCounter = 0;

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
	InitWindow(1, 1, "App");
	SetTargetFPS(appFPS);
	const int width = GetMonitorWidth(0) - windowBorder;
	const int height = GetMonitorHeight(0) - windowBorder;
	printf("GetMonitorWidth(0)-windowBorder = %i\n", width);
	printf("GetMonitorHeight(0)-windowBorder = %i\n", height);
	SetWindowSize(width, height);
	int codepoints[512] = { 0 };
	for (int i = 0; i < 95; i++) codepoints[i] = 32 + i;
	for (int i = 0; i < 255; i++) codepoints[96 + i] = 0x400 + i;
	Font rusFont = LoadFontEx("font.ttf",12,codepoints,512);
	// DRAWLOOP
	while (APPSTATE != CLOSING) {
		BeginDrawing();
		if (APPSTATE == PLANET) {
			if (IsMouseButtonPressed(0)) {
				++clickCounter;
				printf("mouse button clicked in PLANET %i times\n", clickCounter);
			};
			ClearBackground((Color){16,16,16,255});

			// TRAJECTORIES
			DrawCircle(width/2, height/2, 97, (Color){32,32,32,255});
			DrawCircle(width/2, height/2, 96, (Color){16,16,16,255});
			DrawCircle(width/2, height/2, 81, (Color){32,32,32,255});
			DrawCircle(width/2, height/2, 80, (Color){16,16,16,255});
			DrawCircle(width/2, height/2, 65, (Color){32,32,32,255});
			DrawCircle(width/2, height/2, 64, (Color){16,16,16,255});
			DrawCircle(width/2, height/2, 49, (Color){32,32,32,255});
			DrawCircle(width/2, height/2, 48, (Color){16,16,16,255});

			DrawCircle(width/2, height/2, 24, YELLOW);		// SUN
			if (clickCounter > 9) {
				DrawTextEx(
					rusFont,
					"ТЫ",
					(Vector2){
					width/2+20,
					height/2+20},
					16,
					1.0,
					WHITE
				);
			};

			DrawCircle(						// MERCURY
				(width/2)+(48*sin(GetTime()*1.1 + 3)),		// x
				(height/2)+(48*cos(GetTime()*1.1 + 3)),		// y
				4,
				WHITE
			);
			if (clickCounter > 8) {
				DrawTextEx(
					rusFont,
					"МЕРКУРИЙ",
					(Vector2){
					(width/2)+(48*sin(GetTime()*1.1 + 3))+4,
					(height/2)+(48*cos(GetTime()*1.1 + 3))+4},
					16,
					1.0,
					WHITE
				);
			};

			DrawCircle(						// VENUS
				(width/2)+(64*sin(GetTime()*1.0 + 12)),		// x
				(height/2)+(64*cos(GetTime()*1.0 + 12)),	// y
				6,
				(Color){255,100,15,255}
			);
			if (clickCounter > 7) {
				DrawTextEx(
					rusFont,
					"ВЕНЕРА",
					(Vector2){
					(width/2)+(64*sin(GetTime()*1.0 + 12))+5,
					(height/2)+(64*cos(GetTime()*1.0 + 12))+5},
					16,
					1.0,
					WHITE
				);
			};

			DrawCircle(						// EARTH
				(width/2)+(80*sin(GetTime()*0.9 + 1)),		// x
				(height/2)+(80*cos(GetTime()*0.9 + 1)),		// y
				7,
				(Color){15,70,255,255}
			);
			if (clickCounter > 6) {
				DrawTextEx(
					rusFont,
					"ЗЕМЛЯ",
					(Vector2){
					(width/2)+(80*sin(GetTime()*0.9 + 1))+7,
					(height/2)+(80*cos(GetTime()*0.9 + 1))+7},
					16,
					1.0,
					WHITE
				);
			};

			DrawCircle(						// MARS
				(width/2)+(96*sin(GetTime()*0.8 + 42)),		// x
				(height/2)+(96*cos(GetTime()*0.8 + 42)),	// y
				7,
				(Color){250,50,10,255}
			);
			if (clickCounter > 5) {
				DrawTextEx(
					rusFont,
					"МАРС",
					(Vector2){
					(width/2)+(96*sin(GetTime()*0.8 + 42))+7,
					(height/2)+(96*cos(GetTime()*0.8 + 42))+7},
					16,
					1.0,
					WHITE
				);
			};

			DrawCircle(						// JUPITER
				(width/2)+(128*sin(GetTime()*0.7 + 23)),	// x
				(height/2)+(128*cos(GetTime()*0.7 + 23)),	// y
				13,
				(Color){250,200,35,255}
			);
			if (clickCounter > 4) {
				DrawTextEx(
					rusFont,
					"ЮПИТЕР",
					(Vector2){
					(width/2)+(128*sin(GetTime()*0.7 + 23))+11,
					(height/2)+(128*cos(GetTime()*0.7 + 23))+11},
					16,
					1.0,
					WHITE
				);
			};

			DrawCircle(						// SATURN
				(width/2)+(160*sin(GetTime()*0.6 + 7)),		// x
				(height/2)+(160*cos(GetTime()*0.6 + 7)),	// y
				13,
				(Color){250,200,135,255}
			);
			if (clickCounter > 3) {
				DrawTextEx(
					rusFont,
					"САТУРН",
					(Vector2){
					(width/2)+(160*sin(GetTime()*0.6 + 7))+11,
					(height/2)+(160*cos(GetTime()*0.6 + 7))+11},
					16,
					1.0,
					WHITE
				);
			};

			DrawCircle(						// URANUS
				(width/2)+(192*sin(GetTime()*0.5 + 86)),	// x
				(height/2)+(192*cos(GetTime()*0.5 + 86)),	// y
				6,
				(Color){90,190,255,255}
			);
			if (clickCounter > 2) {
				DrawTextEx(
					rusFont,
					"УРАН",
					(Vector2){
					(width/2)+(192*sin(GetTime()*0.5 + 86))+9,
					(height/2)+(192*cos(GetTime()*0.5 + 86))+9},
					16,
					1.0,
					WHITE
				);
			};

			DrawCircle(						// NEPTUNE
				(width/2)+(208*sin(GetTime()*0.4 + 13)),	// x
				(height/2)+(208*cos(GetTime()*0.4 + 13)),	// y
				7,
				(Color){0,110,255,255}
			);
			if (clickCounter > 1) {
				DrawTextEx(
					rusFont,
					"НЕПТУН",
					(Vector2){
					(width/2)+(208*sin(GetTime()*0.4 + 13))+9,
					(height/2)+(208*cos(GetTime()*0.4 + 13))+9},
					16,
					1.0,
					WHITE
				);
			};
		};
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
