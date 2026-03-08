#include <ncurses/ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MIN_Y 2
#define STOP_GAME KEY_F(10)
#define MAX_TAIL_SIZE 100
#define START_TAIL_SIZE 10
#define MAX_FOOD_SIZE 20
#define FOOD_EXPIRE_SECONDS 10
#define FPS 10
#define CONTROLS 3

const double FRAME_MS = 1000. / FPS;
// Directions
enum {
  LEFT = 1,
  UP,
  RIGHT,
  DOWN,
};

// Codes of buttons to control snake
struct control_buttons {
  int down;
  int up;
  int left;
  int right;
};

struct control_buttons default_controls[CONTROLS] = {
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
    {'S', 'W', 'A', 'D'},
    {'s', 'w', 'a', 'd'}};

/*
 x,y - coords of snake head
 direction - current moving direction
 tsize - tail size, array of coords x & y
 *tail - tail pointer
 */
typedef struct snake_t {
  int x;
  int y;
  int direction;
  size_t tsize;
  struct tail_t *tail;
  struct control_buttons *controls;
} snake_t;

/*
 Tail segment
 */
typedef struct tail_t {
  int x;
  int y;
} tail_t;

void initHead(struct snake_t *head, int x, int y) {
  head->x = x;
  head->y = y;
  head->direction = RIGHT;
}

void initTail(struct tail_t *t, int head_x, int head_y, size_t size) {
  for (size_t i = 0; i < size; i++) {
    t[i].x = head_x - (int)i - 1;
    t[i].y = head_y;
  }
}

void initSnake(snake_t *snake, size_t size, int x, int y) {
  tail_t *tail = malloc(MAX_TAIL_SIZE * sizeof(tail_t));
  initHead(snake, x, y);
  initTail(tail, x, y, MAX_TAIL_SIZE);
  snake->tail = tail; // connect tail to head
  snake->tsize = size;
  snake->controls = default_controls;
}

/*
 Food
*/
struct food {
  int x;
  int y;
  time_t put_time;
  char point;
  uint8_t enable;
} food[MAX_FOOD_SIZE];

void initFood(struct food f[], size_t size) {
  struct food init = {0, 0, 0, 0, 0};
  for (size_t i = 0; i < size; i++) {
    f[i] = init;
  }
}
/*
 Обновить/разместить текущее зерно на поле
 */
void putFoodSeed(struct food *fp) {
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
void putFood(struct food f[], size_t number_seeds) {
  for (size_t i = 0; i < number_seeds; i++) {
    putFoodSeed(&f[i]);
  }
}

void refreshFood(struct food f[], int nfood) {
  for (size_t i = 0; i < nfood; i++) {
    if (f[i].put_time) {
      if (!f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS) {
        putFoodSeed(&f[i]);
      }
    }
  }
}

void repairSeed(struct food f[], size_t nfood, struct snake_t *snake) {
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

void update(snake_t *snake) {
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

// Проверка того, является ли какое-то из зерен съеденным,
int haveEat(struct snake_t *head, struct food f[]) {
  //...нужно написать код...//
  return 0;
}

/*
 Увеличение хвоста на 1 элемент
 */
void addTail(struct snake_t *head) {
  //...нужно написать код...//
}

int check_self_collision(snake_t *snake) {
  for (size_t i = 0; i < snake->tsize; i++) {
    int tail_x = snake->tail[i].x, tail_y = snake->tail[i].y;
    if ((snake->x == tail_x) && (snake->y == tail_y)) {
      return 1;
    }
  }
  return 0;
}

int checkDirection(snake_t *snake, int intention) {
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

void input(struct snake_t *snake, const int32_t key) {

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

void draw(snake_t *snake) {
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

void draw_game_over() {
  timeout(-1);
  mvprintw(0, 0, "Game Over. Press any button to exit");
  getch();
}

int main() {
  snake_t *snake = (snake_t *)malloc(sizeof(snake_t));
  initSnake(snake, START_TAIL_SIZE, 10, 10);
  initscr();
  keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
  raw();                // Откдючаем line buffering
  noecho();             // Отключаем echo() режим при вызове getch
  curs_set(FALSE);      // Отключаем курсор

  // Start screen with snake
  draw(snake);
  getch(); // Wait for start;

  timeout(0); // Отключаем таймаут после нажатия клавиши в цикле

  int key_pressed = 0;
  while (key_pressed != STOP_GAME) {
    clock_t frame_start = clock();
    key_pressed = getch(); // Считываем клавишу
    input(snake, key_pressed);
    update(snake);
    draw(snake);

    if (check_self_collision(snake)) {
      draw_game_over();
      break;
    }

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