#ifndef FOOD_H
#define FOOD_H

#include <stdint.h>
#include <time.h>

#include <snake.h>

#define MAX_FOOD_SIZE 20
#define FOOD_EXPIRE_SECONDS 10
#define SEED_NUMBER 3

/*
 Food
*/
typedef struct Food {
  int x;
  int y;
  time_t put_time;
  char point;
  uint8_t enable;
} Food;

void initFood(Food f[], size_t size);
void putFoodSeed(Food *fp);
void putFood(Food f[], size_t number_seeds);
void refreshFood(Food f[], size_t nfood);
void repairSeed(Food f[], size_t nfood, Snake *snake);
int haveEat(Snake *snake, Food food[], size_t food_number);

#endif