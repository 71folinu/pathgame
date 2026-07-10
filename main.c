// TODO-s:
// make a new physics_test button

// Inclusion of external libraries
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Global constants
const int BannerFontSize = 32;
const int appFPS = 40;
const int windowBorder = 32;

// Global enums
enum BUTTON_ANCHOR { UL, UR, LL, LR };
enum APPSTATE_ENUM { CLOSING, LOADING_APP, MAIN_MENU, PLANET, PHYSICS_TEST, TRANSITION, PATHGAME };
// enum APPSTATE_ENUM APPSTATE = LOADING_APP;
enum APPSTATE_ENUM APPSTATE = PATHGAME;

// Global appstate counters
int loadingAppCounter = 0;
int clickCounter = 0;
int transitionCounter = 0;

#include "buttons.c"

// Draw banner in the middle of the screen. Used when loading for the first time
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

// Entrypoint
int main(void) {
	printf("ENTERED MAIN\n");
	InitWindow(1, 1, "App");

	// Window setup
	SetTargetFPS(appFPS);
	const int width = GetMonitorWidth(0) - windowBorder;
	const int height = GetMonitorHeight(0) - windowBorder;
	printf("GetMonitorWidth(0)-windowBorder = %i\n", width);
	printf("GetMonitorHeight(0)-windowBorder = %i\n", height);
	SetWindowSize(width, height);

	// Font setup for PLANET
	int codepoints[512] = { 0 };
	for (int i = 0; i < 95; i++) codepoints[i] = 32 + i;		// The standard codepoints for english
	for (int i = 0; i < 255; i++) codepoints[96 + i] = 0x400 + i;	// Codepoints for russian
	Font rusFont = LoadFontEx("font.ttf",12,codepoints,512);

	// Setup for pathgame
	Camera3D playerCamera =  { 0 };
	playerCamera.position = (Vector3){ 0.0f, 1.7f, 0.0f };    // Camera position
	playerCamera.target = (Vector3){ 1.0f, 1.7f, 0.0f };      // Camera looking at point
	playerCamera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	playerCamera.fovy = 60.0f;                                // Camera field-of-view Y
	playerCamera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	#include "physicsTestVars.c"
	while (APPSTATE != CLOSING) {
		BeginDrawing();

		// Pathgame
		if (APPSTATE == PATHGAME) {
			if (IsKeyPressed(KEY_ESCAPE)) APPSTATE = TRANSITION;
			if (IsKeyDown(KEY_W)) {
				playerCamera.position.x += 0.05;
				playerCamera.target = Vector3Add(playerCamera.position,(Vector3){ 1.0f, 0.0f, 0.0f });
				printf("playerCamera.position.x is now %f\n",playerCamera.position.x);
				printf("W pressed\n");
			};
			ClearBackground((Color){0,0,31,255});
			BeginMode3D(playerCamera);
				DrawCube((Vector3){0,-0.01,0},32,0.01,32,DARKGREEN);
				DrawGrid(32,1);
			EndMode3D();
		};

		#include "physicsTest.c"
		#include "planet.c"
		processButtons();

		// Main menu
		if (APPSTATE == MAIN_MENU) {
			ClearBackground(DARKGRAY);
			if (IsKeyPressed(KEY_ESCAPE)) APPSTATE = CLOSING;
		};

		// Loading screen after launch
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

		// Transition between a substate and main menu
		if (APPSTATE == TRANSITION) {
			transitionCounter += 1;
			if (transitionCounter > 1) {
				APPSTATE = MAIN_MENU;
				transitionCounter = 0;
			};
		};

		EndDrawing();
	};
	CloseWindow();
	return 0;
}
