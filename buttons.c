// buttons.c

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
