#include "snake.h"
#include <controls.h>
#include <ncurses/ncurses.h>

void input(Snake *snake, const int32_t key) {

  int intention = 0;

  if (key == snake->controls.down) {
    intention = DOWN;

  } else if (key == snake->controls.up) {
    intention = UP;

  } else if (key == snake->controls.right) {
    intention = RIGHT;

  } else if (key == snake->controls.left) {
    intention = LEFT;
  }

  if (!intention) {
    return;
  }

  if (!checkDirection(snake, intention)) {
    return;
  }

  snake->direction = intention;
}