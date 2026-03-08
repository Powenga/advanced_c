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
#define START_TAIL_SIZE 3
#define FPS 10
#define PLAYERS 2

const double FRAME_MS = 1000. / FPS;

void draw_food(Food food[], size_t food_count) {
  for (size_t i = 0; i < food_count; i++) {
    mvprintw(food[i].y, food[i].x, "%c", '$');
  }
}

void draw(Snake *snakes[], Food food[]) {
  char head_symbol = '@';
  char tail_symbol = '*';
  // Crear screen
  erase();

  // Welcome text
  mvprintw(0, 0, "Use arrows for control. Press 'F10' for EXIT");

  for (size_t i = 0; i < PLAYERS; i++) {
    Snake *current_snake = snakes[i];
    // Draw new head
    mvprintw(current_snake->y, current_snake->x, "%c", head_symbol);

    for (size_t j = 0; j < current_snake->tsize; j++) {
      mvprintw(current_snake->tail[j].y, current_snake->tail[j].x, "%c",
               tail_symbol);
    }
  }

  draw_food(food, SEED_NUMBER);
}

void draw_game_over() {
  timeout(-1);
  mvprintw(0, 0, "Game Over. Press any button to exit");
  getch();
}

int main() {
  struct Snake *snakes[PLAYERS];
  struct Food food[MAX_FOOD_SIZE];

  struct ControlButtons default_controls[CONTROLS] = {
      {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
      {'s', 'w', 'a', 'd'},
      {'S', 'W', 'A', 'D'}};

  for (int i = 0; i < PLAYERS; i++) {
    snakes[i] = (Snake *)malloc(sizeof(Snake));
    initSnake(snakes[i], START_TAIL_SIZE, 10 + i * 10, 10 + i * 10,
              default_controls[i]);
    // Start screen with snake
  }

  initFood(food, MAX_FOOD_SIZE);
  putFood(food, SEED_NUMBER); // Кладем зерна
  initscr();
  keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
  raw();                // Откдючаем line buffering
  noecho();             // Отключаем echo() режим при вызове getch
  curs_set(FALSE);      // Отключаем курсор

  draw(snakes, food);
  getch(); // Wait for start;

  timeout(0); // Отключаем таймаут после нажатия клавиши в цикле

  int key_pressed = 0;
  while (key_pressed != STOP_GAME) {
    clock_t frame_start = clock();
    key_pressed = getch(); // Считываем клавишу

    for (int i = 0; i < PLAYERS; i++) {
      input(snakes[i], key_pressed);
      update_snake(snakes[i]);
      if (check_self_collision(snakes[i])) {
        draw_game_over();
        break;
      }
      if (haveEat(snakes[i], food, SEED_NUMBER)) {
        addTail(snakes[i]);
      }

      repairSeed(food, SEED_NUMBER, snakes[i]);
    }

    draw(snakes, food);
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
  for (int i = 0; i < PLAYERS; i++) {

    free(snakes[i]->tail);
    free(snakes[i]);
  }
  endwin(); // Завершаем режим curses mod
  return 0;
}