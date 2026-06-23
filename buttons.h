// buttons.h

// INCLUDES
#include <raylib.h>
#include <stdbool.h>

// ENUMS
enum BUTTON_ANCHOR { UL, UR, LL, LR };

// STRUCTURES
struct BUTTON {
	int x;
	int y;
	int w;
	int h;
	Color fillColor;
	Color textColor;
	char text[64];
	int textFontSize;
	bool pressed;
	enum BUTTON_ANCHOR anchor;
	int counter;
	bool wasPressed;
};

// STATIC STRUCT INSTANCES
extern struct BUTTON mainMenuExitButton;

// FUNCTIONS
// check if mouse is hovering over a button
bool isMouseOverButton(struct BUTTON button);
// just render button on screen, not make it clickable
void renderButton(struct BUTTON button);
bool isButtonPressed(struct BUTTON button);
void processButtons(void);
