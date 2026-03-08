#include <ncurses/ncurses.h>
#include <snake.h>
#include <stdlib.h>

#define MAX_TAIL_SIZE 100

void initHead(struct Snake *head, int x, int y) {
  head->x = x;
  head->y = y;
  head->direction = RIGHT;
}

void initTail(struct Tail *t, int head_x, int head_y, size_t size) {
  for (size_t i = 0; i < size; i++) {
    t[i].x = head_x - (int)i - 1;
    t[i].y = head_y;
  }
}

void initSnake(Snake *snake, size_t size, int x, int y,
               ControlButtons *controls) {
  Tail *tail = malloc(MAX_TAIL_SIZE * sizeof(Tail));
  initHead(snake, x, y);
  initTail(tail, x, y, MAX_TAIL_SIZE);
  snake->tail = tail; // connect tail to head
  snake->tsize = size;
  snake->controls = controls;
}

int check_self_collision(Snake *snake) {
  for (size_t i = 0; i < snake->tsize; i++) {
    int tail_x = snake->tail[i].x, tail_y = snake->tail[i].y;
    if ((snake->x == tail_x) && (snake->y == tail_y)) {
      return 1;
    }
  }
  return 0;
}

int checkDirection(Snake *snake, int intention) {
  if (snake->tsize > 0) {
    if ((snake->direction == RIGHT && intention == LEFT) ||
        (snake->direction == LEFT && intention == RIGHT) ||
        (snake->direction == UP && intention == DOWN) ||
        (snake->direction == DOWN && intention == UP)) {
      // Reverse detected
      return 0;
    }
  }
  // OK
  return 1;
}

/*
 Увеличение хвоста на 1 элемент
 */
void addTail(struct Snake *head) {
  //...нужно написать код...//
}

void update_snake(Snake *snake) {
  int max_x = 0, max_y = 0;
  getmaxyx(stdscr, max_y, max_x); // macro - get terminal size

  // Update tail firstly
  for (size_t i = snake->tsize - 1; i > 0; i--) {
    snake->tail[i] = snake->tail[i - 1];
  }

  snake->tail[0].x = snake->x;
  snake->tail[0].y = snake->y;

  // Move head to new position
  switch (snake->direction) {
  case LEFT:

    snake->x--;
    if (snake->x < 0) // screen left border, move to  right border
    {

      snake->x = max_x - 1;
    }
    break;
  case RIGHT:
    snake->x++;
    if (snake->x >= max_x) {
      snake->x = 0;
    }
    break;
  case UP:
    snake->y--;
    if (snake->y < 1) // One row to welcome text
    {
      snake->y = max_y - 1;
    }
    break;
  case DOWN:
    snake->y++;
    if (snake->y >= max_y) {
      snake->y = 1; // One row to welcome text
    }
    break;
  default:
    break;
  }
};
