#include <controls.h>
#include <ncurses/ncurses.h>

void input(Snake *snake, const int32_t key) {

  int intention = 0;

  for (size_t i = 0; i < CONTROLS; i++) {
    if (key == snake->controls[i].down) {
      intention = DOWN;
      break;
    } else if (key == snake->controls[i].up) {
      intention = UP;
      break;
    } else if (key == snake->controls[i].right) {
      intention = RIGHT;
      break;
    } else if (key == snake->controls[i].left) {
      intention = LEFT;
      break;
    }
  }

  if (!intention) {
    return;
  }

  if (!checkDirection(snake, intention)) {
    return;
  }

  snake->direction = intention;
}