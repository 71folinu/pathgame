// TODO-s:
// split it into files by UNITY BUILD method
// make em throwable (like physics)?
// pathgame button in menu

enum BUTTON_ANCHOR { UL, UR, LL, LR };

#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const int BannerFontSize = 32;
const int appFPS = 32;
const int windowBorder = 32;

enum APPSTATE_ENUM { CLOSING, LOADING_APP, MAIN_MENU, PLANET, PHYSICS_TEST };
enum APPSTATE_ENUM APPSTATE = LOADING_APP;

int loadingAppCounter = 0;
int clickCounter = 0;

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
	int codepoints[512] = { 0 };
	for (int i = 0; i < 95; i++) codepoints[i] = 32 + i;
	for (int i = 0; i < 255; i++) codepoints[96 + i] = 0x400 + i;
	Font rusFont = LoadFontEx("font.ttf",12,codepoints,512);
	float physics_test_ballX = width/2;
	float physics_test_ballXV = 8;
	float physics_test_ballY = height/2;
	float physics_test_ballYV = 8;
	float physics_test_ballRadius = 32;
	float physics_test_def_airDrag = 0.99;
	float physics_test_airDrag = 0.99;
	while (APPSTATE != CLOSING) {
		BeginDrawing();
		if (APPSTATE == PHYSICS_TEST) {
			if (IsMouseButtonDown(0)) {
				physics_test_airDrag = 0.90;
				physics_test_ballXV += 0.05*(GetMouseX() - physics_test_ballX);
				physics_test_ballYV += 0.05*(GetMouseY() - physics_test_ballY);
			};
			if (IsMouseButtonReleased(0)) physics_test_airDrag = physics_test_def_airDrag;
			physics_test_ballYV += 1.5;
			physics_test_ballY += physics_test_ballYV;
			physics_test_ballX += physics_test_ballXV;
			if (physics_test_ballY+physics_test_ballRadius > height) {
				physics_test_ballY = height - physics_test_ballRadius;
				physics_test_ballYV *= -0.9;
			};
			if (physics_test_ballX+physics_test_ballRadius > width) {
				physics_test_ballX = width - physics_test_ballRadius;
				physics_test_ballXV *= -0.9;
			};
			if (physics_test_ballX-physics_test_ballRadius < 0) {
				physics_test_ballX = 0 + physics_test_ballRadius;
				physics_test_ballXV *= -0.9;
			};
			if (physics_test_ballY-physics_test_ballRadius < 0) {
				physics_test_ballY = 0 + physics_test_ballRadius;
				physics_test_ballYV *= -0.9;
			};
			physics_test_ballXV *= physics_test_airDrag;
			physics_test_ballYV *= physics_test_airDrag;
			ClearBackground(GRAY);
			DrawCircle(physics_test_ballX,physics_test_ballY,physics_test_ballRadius,WHITE);
		};
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
	CloseWindow();
	return 0;
}
