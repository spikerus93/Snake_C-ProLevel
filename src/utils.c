#include <utils.h>

#define MAX_X 15
#define MAX_Y 15

#define START_TAIL_SIZE 2
#define MAX_TAIL_SIZE 100

#define DELAY 100
#define PAUSE 1000
#define SPEED_UP 5

#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"

enum
{
    LEFT = 1,
    RIGHT,
    UP,
    DOWN,
    CONTROLS = 3
};

/* TO DO Сделать выбор полноценным:
Логика классического режима игры (MODE_CLASSIC) включает управление движением змеи, проверку столкновений с границами или хвостом, обновление игровой области и добавление новых частей змеи при поедании еды.
Искусственный интеллект (MODE_AI) аналогично работает, но включает функцию авто-пилот на другую змейку.
*/

enum
{
    MODE_CLASSIC,
    MODE_AI
};
char *modes[] = {"Classic_Mode", "AI_Mode"};

typedef struct tail_t
{
    int x, y;
} tail_t;

typedef struct food_t
{
    int x, y;
    int hasEaten;
    int color;
} food_t;

typedef struct snake_t
{
    int x, y;
    int direction;
    food_t food;
    struct tail_t *tail;
    size_t tsize;
    int level;
    int speed;
    int color;
} snake_t;

_Bool GameOver = FALSE;

void levelUp(snake_t *snake)
{
    snake->level += 1;
}

void speedUp(snake_t *snake)
{
    snake->speed -= SPEED_UP;
}

void delayGame(int ms)
{
    int startTime = clock();
    while ((clock() - startTime) < ms)
        ;
}

bool isInsideField(int x, int y)
{
    return x >= 0 || x < MAX_X - 1 || y >= 0 || y < MAX_Y - 1;
}

_Bool isSnakeInTail(snake_t *snake)
{
    for (size_t i = 1; i < snake->tsize; i++)
    {
        if (snake->x == snake->tail[i].x && snake->y == snake->tail[i].y)
            return 1;
    }
    return 0;
}