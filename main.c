// Inclusion of external libraries
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// Global variables
bool playerFastRun = false;
float ViewSensivity = 0.5;
// Global constants
const int BannerFontSize = 32;
const int appFPS = 40;
const int windowBorder = 32;
// Global enums
enum BUTTON_ANCHOR { UL, UR, LL, LR };
enum APPSTATE_ENUM { CLOSING, LOADING_APP, MAIN_MENU, PLANET, PHYSICS_TEST, TRANSITION, PATHGAME, SETTINGS_SCREEN };
// enum APPSTATE_ENUM APPSTATE = LOADING_APP;
// enum APPSTATE_ENUM APPSTATE = SETTINGS_SCREEN;
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
// Draw streetlight
void DrawStreetlight(Vector3 BasePos) {
	Color StreetlightColor = (Color){40,40,50,255};
	Color LitStreetlightColor = (Color){70,80,70,255};
	Color LitGroundColor = (Color){30,100,20,255};
	Color LitPathColor = (Color){100,100,100,255};
	// Base
	DrawCylinder(
		BasePos,
		0.1,
		0.1,
		4.0,
		6,
		StreetlightColor
	);
	// Lit base
	DrawCylinder(
		Vector3Add(BasePos,(Vector3){0,0,-0.02}),
		0.11,
		0.11,
		4.0,
		6,
		LitStreetlightColor
	);
	// Light roof
	DrawCubeV(
		Vector3Add(BasePos,(Vector3){0,4.0,-0.3}),
		(Vector3){0.3,0.1,0.9},
		StreetlightColor
	);
	// Light itself
	DrawCubeV(
		Vector3Add(BasePos,(Vector3){0,3.9,-0.5}),
		(Vector3){0.25,0.05,0.45},
		YELLOW
	);
	// Lit area of the ground
	DrawCylinder(
		Vector3Add(BasePos,(Vector3){0,0,-0.5}),
		4.0,
		4.0,
		0.01,
		10,
		LitGroundColor
	);
	// Lit area of the path
	DrawTriangle3D(
		Vector3Add((Vector3){-3.8,0.011,-1.74},BasePos),
		Vector3Add((Vector3){3.8,0.011,-1.74},BasePos),
		Vector3Add((Vector3){-3.26,0.011,-2.5},BasePos),
		LitPathColor
	);
	DrawTriangle3D(
		Vector3Add((Vector3){3.8,0.011,-1.74},BasePos),
		Vector3Add((Vector3){3.26,0.011,-2.5},BasePos),
		Vector3Add((Vector3){-3.26,0.011,-2.5},BasePos),
		LitPathColor
	);
	DrawPlane(
		Vector3Add(BasePos,(Vector3){0,0.011,-1.125}),
		(Vector2){7.61,1.25},
		LitPathColor
	);
}
// Entrypoint
int main(void) {
	printf("ENTERED MAIN\n");
	InitWindow(1, 1, "App");
	// Window setup
	SetTargetFPS(appFPS);
	width = GetMonitorWidth(0) - windowBorder;
	height = GetMonitorHeight(0) - windowBorder;
	printf("GetMonitorWidth(0)-windowBorder = %i\n", width);
	printf("GetMonitorHeight(0)-windowBorder = %i\n", height);
	SetWindowSize(width, height);
	// Font setup for PLANET
	int codepoints[512] = { 0 };
	for (int i = 0; i < 95; i++) codepoints[i] = 32 + i;		// The standard codepoints for english
	for (int i = 0; i < 255; i++) codepoints[96 + i] = 0x400 + i;	// Codepoints for russian
	Font rusFont = LoadFontEx("font.ttf",12,codepoints,512);
	// Setup for pathgame
	bool EnableDrawFPS = true;
	float playerSpeed = 0;
	float playerWalkSpeed = 0.1;
	float playerRunSpeed = 0.2;
	float playerRotation = 90;
	float playerTilt = 0;
	float playerRotationSpeed = 8;
	float playerHeight = 1.4;
	float renderDist = 512;
	Camera3D playerCamera =  { 0 };
	playerCamera.position = (Vector3){ 0.0f, playerHeight, 0.0f };	// Camera position
	playerCamera.target = (Vector3){ 1.0f, 1.7f, 0.0f };		// Camera looking at point
	playerCamera.up = (Vector3){ 0.0f, 1.0f, 0.0f };		// Camera up vector (rotation towards target)
	playerCamera.fovy = 70.0f;					// Camera field-of-view Y
	playerCamera.projection = CAMERA_PERSPECTIVE;			// Camera mode type
	Model PoleModel = LoadModel("pole.glb");
	#include "physicsTestVars.c"
	while (APPSTATE != CLOSING) {
		BeginDrawing();
		// Settings screen
		if (APPSTATE == SETTINGS_SCREEN) {
			ClearBackground(DARKGRAY);
			processSettingsScreenButtons();
			if (IsKeyPressed(KEY_ESCAPE)) APPSTATE = TRANSITION;
		};
		// Pathgame
		if (APPSTATE == PATHGAME) {
			HideCursor();
			if (IsKeyPressed(KEY_ESCAPE)) APPSTATE = TRANSITION;
			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				if (playerFastRun == true) {
					playerSpeed = playerRunSpeed*5;
				} else {
					playerSpeed = playerRunSpeed;
				};
			} else {
				playerSpeed = playerWalkSpeed;
			};
			// Player movement processing
			if (IsKeyDown(KEY_W)) {
				playerCamera.position.x += sin(playerRotation*DEG2RAD)*playerSpeed;
				playerCamera.position.z += cos(playerRotation*DEG2RAD)*playerSpeed;
			};
			if (IsKeyDown(KEY_S)) {
				playerCamera.position.x -= sin(playerRotation*DEG2RAD)*playerSpeed;
				playerCamera.position.z -= cos(playerRotation*DEG2RAD)*playerSpeed;
			};
			if (IsKeyDown(KEY_D)) {
				playerCamera.position.z += sin(playerRotation*DEG2RAD)*playerSpeed;
				playerCamera.position.x -= cos(playerRotation*DEG2RAD)*playerSpeed;
			};
			if (IsKeyDown(KEY_A)) {
				playerCamera.position.z -= sin(playerRotation*DEG2RAD)*playerSpeed;
				playerCamera.position.x += cos(playerRotation*DEG2RAD)*playerSpeed;
			};
			// Simple player rotation processing
			if (IsKeyDown(KEY_H) || IsKeyDown(KEY_LEFT)) playerRotation += playerRotationSpeed*ViewSensivity;
			if (IsKeyDown(KEY_L) || IsKeyDown(KEY_RIGHT)) playerRotation -= playerRotationSpeed*ViewSensivity;
			// Mouse look processing
			playerRotation -= (float)(GetMouseX()-width/2)/4.0;
			if ((float)GetMouseX()-(float)width/2.0) {
				DrawText("MOUSE MOVING",50,50,16,WHITE);
			};
			playerTilt -= (float)(GetMouseY()-height/2.0)/4;
			SetMousePosition(width/2,height/2);
			playerCamera.target = (Vector3) {	playerCamera.position.x+cos(playerTilt*DEG2RAD)*sin(playerRotation*DEG2RAD),
								playerHeight + sin(playerTilt*DEG2RAD),
								playerCamera.position.z+cos(playerTilt*DEG2RAD)*cos(playerRotation*DEG2RAD)};
			// Rendering
			ClearBackground((Color){0,0,31,255});
			BeginMode3D(playerCamera);
				// Simple player shadow
				// Transparency works only with models, so cancelled for now
				// DrawCylinder((Vector3){playerCamera.position.x,playerCamera.position.y-playerHeight+0.1,playerCamera.position.z}, 5.5, 5.5, 0.1, 9, (Color){0,0,0,31});
				// Ground
				DrawPlane((Vector3){0,-0.01,0},(Vector2){renderDist,renderDist/4},(Color){20,40,10,255});
				// Path
				DrawCube((Vector3){0,0,0},renderDist,0.01,2.0,(Color){ 40, 40, 40, 255 });
				// Dirt path
				DrawCube((Vector3){-renderDist/4,0,0},renderDist/2,0.02,3,(Color){ 40, 20, 20, 255 });
				// Modelled pole
				DrawModel(PoleModel,(Vector3){8,0,0},1.0,WHITE);
				// Streetlights
				for (int i = 0; i < 32-6; i++) {
					if (i == 6) {continue;};
					DrawStreetlight((Vector3){i*10+16,0,1.5});
				};
				// Grid for debug
				// DrawGrid(renderDist,1);
			EndMode3D();
			// Invisible walls
			if (playerCamera.position.x < -renderDist/4) {
				playerCamera.position.x += (playerWalkSpeed+playerRunSpeed)/2;
			};
			if (playerCamera.position.z < -renderDist/16) {
				playerCamera.position.z += (playerWalkSpeed+playerRunSpeed)/2;
			};
			if (playerCamera.position.z > renderDist/16) {
				playerCamera.position.z -= (playerWalkSpeed+playerRunSpeed)/2;
			};
			if (EnableDrawFPS) {
				DrawFPS(10,10);
			};
		};
		#include "physicsTest.c"
		#include "planet.c"
		// Main menu
		if (APPSTATE == MAIN_MENU) {
			ClearBackground(DARKGRAY);
			processMainMenuButtons();
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
