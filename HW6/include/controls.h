#ifndef CONTROLS_H
#define CONTROLS_H

#include <ncurses/ncurses.h>
#include <snake.h>

#define CONTROLS 3

typedef struct Snake Snake;

// Codes of buttons to control snake
typedef struct ControlButtons {
  int down;
  int up;
  int left;
  int right;
} ControlButtons;

void input(Snake *snake, const int32_t key);

#endif