#include <ncurses/ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <controls.h>
#include <food.h>
#include <snake.h>

#define STOP_GAME KEY_F(10)
#define START_TAIL_SIZE 10
#define FPS 10

const double FRAME_MS = 1000. / FPS;

void draw_snake(Snake *snake) {
  char head_symbol = '@';
  char tail_symbol = '*';
  // Crear screen
  erase();

  // Welcome text
  mvprintw(0, 0, "Use arrows for control. Press 'F10' for EXIT");

  // Draw new head
  mvprintw(snake->y, snake->x, "%c", head_symbol);

  for (size_t i = 0; i < snake->tsize; i++) {

    mvprintw(snake->tail[i].y, snake->tail[i].x, "%c", tail_symbol);
  }
}

void draw_seads() {
}

void draw_game_over() {
  timeout(-1);
  mvprintw(0, 0, "Game Over. Press any button to exit");
  getch();
}

int main() {
  Snake *snake = (Snake *)malloc(sizeof(Snake));
  struct Food food[MAX_FOOD_SIZE];

  struct ControlButtons default_controls[CONTROLS] = {
      {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
      {'S', 'W', 'A', 'D'},
      {'s', 'w', 'a', 'd'}};

  initSnake(snake, START_TAIL_SIZE, 10, 10, default_controls);
  initFood(food, MAX_FOOD_SIZE);
  putFood(food, SEED_NUMBER); // Кладем зерна
  initscr();
  keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
  raw();                // Откдючаем line buffering
  noecho();             // Отключаем echo() режим при вызове getch
  curs_set(FALSE);      // Отключаем курсор

  // Start screen with snake
  draw_snake(snake);
  getch(); // Wait for start;

  timeout(0); // Отключаем таймаут после нажатия клавиши в цикле

  int key_pressed = 0;
  while (key_pressed != STOP_GAME) {
    clock_t frame_start = clock();
    key_pressed = getch(); // Считываем клавишу
    input(snake, key_pressed);
    update_snake(snake);
    draw_snake(snake);

    if (check_self_collision(snake)) {
      draw_game_over();
      break;
    }
    refreshFood(food, SEED_NUMBER);

    refresh();
    clock_t frame_end = clock();
    // Check iteration duration
    double elapsed_ms =
        (double)(frame_end - frame_start) * 1000 / CLOCKS_PER_SEC;

    if (elapsed_ms < FRAME_MS) {
      usleep((FRAME_MS - elapsed_ms) * 1000);
    }
  }
  free(snake->tail);
  free(snake);
  endwin(); // Завершаем режим curses mod
  return 0;
}