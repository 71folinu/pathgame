// TODO-s:
// split it into files by UNITY BUILD method
// pathgame button in menu
// make a new physics_test button
// make the LOADING banner not flash when returning from appstate

enum BUTTON_ANCHOR { UL, UR, LL, LR };

#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const int BannerFontSize = 32;
const int appFPS = 40;
const int windowBorder = 32;

enum APPSTATE_ENUM { CLOSING, LOADING_APP, MAIN_MENU, PLANET, PHYSICS_TEST, TRANSITION };
enum APPSTATE_ENUM APPSTATE = LOADING_APP;

int loadingAppCounter = 0;
int clickCounter = 0;
int transitionCounter = 0;

#include "buttons.c"

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
	printf("ENTERED MAIN\n");
	InitWindow(1, 1, "App");
	SetTargetFPS(appFPS);
	const int width = GetMonitorWidth(0) - windowBorder;
	const int height = GetMonitorHeight(0) - windowBorder;
	printf("GetMonitorWidth(0)-windowBorder = %i\n", width);
	printf("GetMonitorHeight(0)-windowBorder = %i\n", height);
	SetWindowSize(width, height);

	// font setup for PLANET
	int codepoints[512] = { 0 };
	for (int i = 0; i < 95; i++) codepoints[i] = 32 + i;
	for (int i = 0; i < 255; i++) codepoints[96 + i] = 0x400 + i;
	Font rusFont = LoadFontEx("font.ttf",12,codepoints,512);

	#include "physicsTestVars.c"
	while (APPSTATE != CLOSING) {
		BeginDrawing();
		#include "physicsTest.c"
		#include "planet.c"
		processButtons();
		if (APPSTATE == MAIN_MENU) {
			ClearBackground(DARKGRAY);
			if (IsKeyPressed(KEY_ESCAPE)) APPSTATE = CLOSING;
		};
		if (APPSTATE == LOADING_APP) {
			ClearBackground(BLACK);
			DrawBanner("LOADING, PLEASE WAIT", width, height);
			if (loadingAppCounter >= appFPS * 1/8) {
				APPSTATE = MAIN_MENU;
				loadingAppCounter = 0;
			};
			loadingAppCounter += 1;
			printf("loadingAppCounter = %i\n", loadingAppCounter);
		};
		if (APPSTATE == TRANSITION) {
			transitionCounter += 1;
			if (transitionCounter > 1) {
				transitionCounter = 0;
				APPSTATE = MAIN_MENU;
			};
		};
		EndDrawing();
		// if (WindowShouldClose()) APPSTATE = CLOSING;
	};
	CloseWindow();
	return 0;
}
