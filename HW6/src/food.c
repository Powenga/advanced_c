#include <food.h>
#include <ncurses/ncurses.h>
#include <stdlib.h>

void initFood(Food f[], size_t size) {
  Food init = {0, 0, 0, 0, 0};
  for (size_t i = 0; i < size; i++) {
    f[i] = init;
  }
}
/*
 Обновить/разместить текущее зерно на поле
 */
void putFoodSeed(Food *fp) {
  int max_x = 0, max_y = 0;
  getmaxyx(stdscr, max_y, max_x);
  fp->x = rand() % (max_x - 1);
  fp->y = rand() % (max_y - 2) + 1; // Не занимаем верхнюю строку
  fp->put_time = time(NULL);
  fp->enable = 1;
}

/*
 Разместить еду на поле
 */
void putFood(Food f[], size_t number_seeds) {
  for (size_t i = 0; i < number_seeds; i++) {
    putFoodSeed(&f[i]);
  }
}

void refreshFood(Food f[], size_t nfood) {
  for (size_t i = 0; i < nfood; i++) {
    if (f[i].put_time) {
      if (!f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS) {
        putFoodSeed(&f[i]);
      }
    }
  }
}

void repairSeed(Food food[], size_t food_count, Snake *snake) {
  for (size_t i = 0; i < snake->tsize; i++)
    for (size_t j = 0; j < food_count; j++) {

      if (snake->tail[i].x == food[j].x && snake->tail[i].y == food[j].y) {
        putFoodSeed(&food[j]);
      }
    }
  for (size_t i = 0; i < food_count; i++)
    for (size_t j = 0; j < food_count; j++) {
      if (i == j) {
        continue;
      }
      if (food[i].x == food[j].x && food[i].y == food[j].y) {
        putFoodSeed(&food[j]);
      }
    }
}

// Проверка того, является ли какое-то из зерен съеденным,
int haveEat(Snake *snake, Food food[], size_t food_number) {
  for (size_t i = 0; i < food_number; i++) {
    if (snake->x == food[i].x && snake->y == food[i].y) {
      food[i].enable = 0;
      return 1;
    }
  }

  return 0;
}