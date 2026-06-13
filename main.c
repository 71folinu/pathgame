#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include "buttons.c"

// CONSTANTS
// TODO: NEED TO BE REPLACED BY DEFINES
const int BannerFontSize = 32;
const int gameFPS = 8;
const int windowBorder = 32;

// GAMESTATE
enum GAMESTATE_ENUM {LOADING_GAME,MAIN_MENU};
int GAMESTATE = LOADING_GAME;

// GLOBAL VARIBLES
int loadingGameCounter = 0;

// DRAW A BANNER IN THE MIDDLE OF THE SCREEN
// TODO: make it semitransparent
void DrawBanner(char text[],int width,int height) {
	int posx = width/2 - MeasureText(text,BannerFontSize)/2;
	int posy = height/2 - BannerFontSize/2;
	DrawRectangle(posx-20,posy-10,MeasureText(text,BannerFontSize)+40,BannerFontSize+20,DARKGRAY);
	DrawText(text,posx,posy,BannerFontSize,WHITE);
}

// ENTRYPOINT
int main(void){

	//WINDOW SETUP
	printf("ENTERED MAIN\n");
	InitWindow(1,1,"PATHGAME");
	SetTargetFPS(gameFPS);
	const int width = GetMonitorWidth(0)-windowBorder;
	const int height = GetMonitorHeight(0)-windowBorder;
	printf("GetMonitorWidth(0)-windowBorder = %i\n",width);
	printf("GetMonitorHeight(0)-windowBorder = %i\n",height);
	SetWindowSize(width,height);

	// DRAWLOOP
	while (!WindowShouldClose()) {
		BeginDrawing();

    // MAIN MENU
    if (GAMESTATE == MAIN_MENU) {
		  ClearBackground(DARKGRAY);
    };

    // LOADING GAME
		if (GAMESTATE == LOADING_GAME) {
		  ClearBackground(BLACK);
			DrawBanner("LOADING, PLEASE WAIT",width,height);
			if (loadingGameCounter>=gameFPS*1){
				GAMESTATE = MAIN_MENU;
			};
			loadingGameCounter += 1;
		  printf("loadingGameCounter = %i\n",loadingGameCounter);
		};

		EndDrawing();
	};

	//CLEANUP ON EXIT
	CloseWindow();
	return 0;
}
