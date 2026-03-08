#ifndef SNAKE_H
#define SNAKE_H

#include <controls.h>

// Directions
enum {
  LEFT = 1,
  UP,
  RIGHT,
  DOWN,
};

/*
 x,y - coords of snake head
 direction - current moving direction
 tsize - tail size, array of coords x & y
 *tail - tail pointer
 */
typedef struct Snake {
  int x;
  int y;
  int direction;
  size_t tsize;
  struct Tail *tail;
  struct ControlButtons controls;
} Snake;

// Tail segment

typedef struct Tail {
  int x;
  int y;
} Tail;

void initHead(Snake *head, int x, int y);
void initTail(Tail *t, int head_x, int head_y, size_t size);
void initSnake(Snake *snake, size_t size, int x, int y,
               struct ControlButtons controls);
int check_self_collision(Snake *snake);
int checkDirection(Snake *snake, int intention);
void addTail(Snake *head);
void update_snake(Snake *snake);

#endif