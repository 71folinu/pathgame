// main.c

// HEADERS
#include "buttons.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"

// APPSTATE
enum APPSTATE_ENUM { LOADING_APP, MAIN_MENU };
int APPSTATE = LOADING_APP;

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

// ENTRYPOINT
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
	while (!WindowShouldClose()) {
		BeginDrawing();
		// MAIN MENU
		if (APPSTATE == MAIN_MENU) {
			ClearBackground(DARKGRAY);
			processButtons();
		};
		// LOADING APP
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
	};

	// CLEANUP ON EXIT
	CloseWindow();
	return 0;
}
