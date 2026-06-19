// buttons.c

// INCLUDES
#include "buttons.h"
#include <raylib.h>
#include <stdbool.h>

// CONSTANTS
const int buttonRectBorder = 32;

// STATIC STRUCT INSTANCES
struct BUTTON mainMenuExitButton = {.x = 64,
                                    .y = 64,
                                    .w = 128,
                                    .h = 16,
                                    .fillColor = {255, 255, 255, 255},
                                    .textColor = {0, 0, 0, 255},
                                    .text = "EXIT GAME",
                                    .textFontSize = 24,
                                    .pressed = false,
                                    .anchor = UR};

// FUNCTIONS

// check if mouse is hovering over a button
bool isMouseOverButton(struct BUTTON button) {

  // setup for calculations
  int x0 = 0;
  int y0 = 0;
  int x1 = 0;
  int y1 = 0;
  if (button.anchor == UL) {
    x0 = button.x - buttonRectBorder;
    y0 = button.y - buttonRectBorder;
    x1 = button.x + button.w + buttonRectBorder;
    y1 = button.y + button.h + buttonRectBorder;
  } else if (button.anchor == UR) {
    x0 = GetScreenWidth() - button.x - button.w - buttonRectBorder;
    y0 = button.y - buttonRectBorder;
    x1 = x0 + button.w + buttonRectBorder * 2;
    y1 = button.y + button.h + buttonRectBorder;
  } else if (button.anchor == LL) {
    x0 = button.x - buttonRectBorder;
    y0 = GetScreenHeight() - button.y - button.h - buttonRectBorder;
    x1 = button.x + button.w + buttonRectBorder;
    y1 = y0 + button.h + buttonRectBorder * 2;
  } else if (button.anchor == LR) {
    x0 = GetScreenWidth() - button.x - button.w - buttonRectBorder;
    y0 = GetScreenHeight() - button.y - button.h - buttonRectBorder;
    x1 = x0 + button.w + buttonRectBorder * 2;
    y1 = y0 + button.h + buttonRectBorder * 2;
  };

  // boundary check
  int mousex = GetMouseX();
  int mousey = GetMouseY();
  if (mousex > x0 && mousex < x1 && mousey > y0 && mousey < y1) {
    return true;
  } else {
    return false;
  };
}

// just render button on screen, not make it clickable
void renderButton(struct BUTTON button) {
  if (button.anchor == UL) {
    DrawRectangle(button.x - buttonRectBorder, button.y - buttonRectBorder,
                  button.w + buttonRectBorder * 2,
                  button.h + buttonRectBorder * 2, button.fillColor);
    int textposx = (button.x + (button.w / 2)) -
                   MeasureText(button.text, button.textFontSize) / 2;
    int textposy = (button.y + (button.h / 2)) - button.textFontSize / 2;
    DrawText(button.text, textposx, textposy, button.textFontSize,
             button.textColor);
  };
  if (button.anchor == UR) {
    DrawRectangle(GetScreenWidth() - button.x - button.w - buttonRectBorder,
                  button.y - buttonRectBorder, button.w + buttonRectBorder * 2,
                  button.h + buttonRectBorder * 2, button.fillColor);
    int textposx = (button.x + (button.w / 2)) -
                   MeasureText(button.text, button.textFontSize) / 2;
    int textposy = (button.y + (button.h / 2)) - button.textFontSize / 2;
    DrawText(button.text,
             GetScreenWidth() - textposx -
                 MeasureText(button.text, button.textFontSize),
             textposy, button.textFontSize, button.textColor);
  };
  if (button.anchor == LL) {
    DrawRectangle(button.x - buttonRectBorder,
                  GetScreenHeight() - button.y - button.h - buttonRectBorder,
                  button.w + buttonRectBorder * 2,
                  button.h + buttonRectBorder * 2, button.fillColor);
    int textposx = (button.x + (button.w / 2)) -
                   MeasureText(button.text, button.textFontSize) / 2;
    int textposy = (button.y + (button.h / 2)) - button.textFontSize / 2;
    DrawText(button.text, textposx,
             GetScreenHeight() - textposy - button.textFontSize,
             button.textFontSize, button.textColor);
  };
  if (button.anchor == LR) {
    DrawRectangle(GetScreenWidth() - button.x - button.w - buttonRectBorder,
                  GetScreenHeight() - button.y - button.h - buttonRectBorder,
                  button.w + buttonRectBorder * 2,
                  button.h + buttonRectBorder * 2, button.fillColor);
    int textposx = (button.x + (button.w / 2)) -
                   MeasureText(button.text, button.textFontSize) / 2;
    int textposy = (button.y + (button.h / 2)) - button.textFontSize / 2;
    DrawText(button.text,
             GetScreenWidth() - textposx -
                 MeasureText(button.text, button.textFontSize),
             GetScreenHeight() - textposy - button.textFontSize,
             button.textFontSize, button.textColor);
  };
}

bool isButtonPressed(struct BUTTON button) {
  if (IsMouseButtonReleased(0) && isMouseOverButton(button)) {
    return true;
  } else {
    return false;
  };
}
