// main.c

// TODO-s:
// split it into files by UNITY BUILD method
// make em throwable (like physics)?
// pathgame button in menu
// physics test button in menu

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

// APPSTATE
enum APPSTATE_ENUM { CLOSING, LOADING_APP, MAIN_MENU, PLANET };
enum APPSTATE_ENUM APPSTATE = LOADING_APP;

// GLOBAL VARS
int loadingAppCounter = 0;
int clickCounter = 0;

#include "buttons.c"

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
		#include "planet.c"
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
