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
  char spoint[2] = {0};
  getmaxyx(stdscr, max_y, max_x);
  mvprintw(fp->y, fp->x, " ");
  fp->x = rand() % (max_x - 1);
  fp->y = rand() % (max_y - 2) + 1; // Не занимаем верхнюю строку
  fp->put_time = time(NULL);
  fp->point = '$';
  fp->enable = 1;
  spoint[0] = fp->point;
  mvprintw(fp->y, fp->x, "%s", spoint);
}

/*
 Разместить еду на поле
 */
void putFood(Food f[], size_t number_seeds) {
  for (size_t i = 0; i < number_seeds; i++) {
    putFoodSeed(&f[i]);
  }
}

void refreshFood(Food f[], int nfood) {
  for (size_t i = 0; i < nfood; i++) {
    if (f[i].put_time) {
      if (!f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS) {
        putFoodSeed(&f[i]);
      }
    }
  }
}

void repairSeed(Food f[], size_t nfood, Snake *snake) {
  for (size_t i = 0; i < snake->tsize; i++)
    for (size_t j = 0; j < nfood; j++) {
      /* Если хвост совпадает с зерном */
      //...нужно написать код...//
    }
  for (size_t i = 0; i < nfood; i++)
    for (size_t j = 0; j < nfood; j++) {
      /* Если два зерна на одной точке */
      //...нужно написать код...//
    }
}

// Проверка того, является ли какое-то из зерен съеденным,
int haveEat(Snake *head, Food f[]) {
  //...нужно написать код...//
  return 0;
}