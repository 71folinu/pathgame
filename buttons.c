// buttons.c

// CONSTANTS
const int buttonRectBorder = 16;

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
};

// STATIC STRUCT INSTANCES
struct BUTTON mainMenuExitButton = {
  .x = 64,
  .y = 64,
  .w = 128,
  .h = 16,
  .fillColor = {255,255,255,255},
  .textColor = {0,0,0,255},
  .text = "EXIT GAME",
  .textFontSize = 24,
  .pressed = false
};

// FUNCTIONS
void renderButton(struct BUTTON button) {
  DrawRectangle(button.x - buttonRectBorder,
                button.y - buttonRectBorder,
                button.w + buttonRectBorder * 2,
                button.h + buttonRectBorder * 2,
                button.fillColor);
  int textposx = (button.x+(button.w/2))-MeasureText(button.text,button.textFontSize)/2;
  int textposy = (button.y+(button.h/2))-button.textFontSize/2;
  DrawText(button.text,textposx,textposy,button.textFontSize,button.textColor);
}
