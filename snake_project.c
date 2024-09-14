/*Змейка
// Домашнее задание
// Проблематика: сейчас змейка “наезжает” на свой хвост

Задача 1. Выбор направления
Написать функцию, которая будет проверять корректность выбранного направления. Змейка
не может наступать на хвост, поэтому необходимо запретить
○ перемещение справа-налево (при движении RIGHT нажатие стрелки влево),
○ перемещение сверху-вниз (при движении UP нажатие стрелки вниз),
○ перемещение слева-направо (при движении LEFT нажатие стрелки вправо),
○ перемещение снизу-вверх (при движении DOWN нажатие стрелки вверх).
Функция должна иметь вид:
int checkDirection(snake_t* snake, int32_t key).
Задача 2. Управление WSAD
Домашнее задание
Добавить возможность управления змейкой клавишами WSAD (вне зависимости от
раскладки и регистра).
Зависимости от регистра в соответствии с таблицей.
W, w Вверх
S, s Вниз
A, a Влево
D, d Вправо

Структура еды
Задача 1
Добавляем в программу структуру еды struct food.
Обновление еды - refreshFood

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define MAX_X 15
#define MAX_Y 15
#define MIN_Y 2

#define SEED_NUMBER 5
#define MAX_FOOD_SIZE 20
#define FOOD_EXPIRE_SECONDS 10

#define START_TAIL_SIZE 3
#define MAX_TAIL_SIZE 20

enum
{
    LEFT = 1,
    RIGHT,
    UP,
    DOWN,
    STOP_GAME = VK_F10,
    CONTROLS = 3
};

typedef struct tail_t
{
    int x, y;
} tail_t;

typedef struct food_t
{
    int x, y;
    time_t put_time;
    char point;
    uint8_t enable;
} food_t;

typedef struct snake_t
{
    int x, y;
    int direction;
    food_t food;
    bool has_eaten;
    struct tail_t *tail;
    size_t tsize;
} snake_t;

struct food
{
    int x, y;
    time_t put_time;
    char point;
    uint8_t enable;
} food[MAX_FOOD_SIZE];

_Bool GameOver = FALSE;

struct snake_t
init_Snake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    snake.direction = 1;

    for (int i = 0; i < (int)tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

void init_Food(struct food f[], size_t size)
{
    struct food init = {0, 0, 0, 0, 0};

    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < size; i++)
    {
        f[i] = init;
    }
}

void print_Snake(struct snake_t snake)
{
    char matrix[MAX_X][MAX_Y];

    for (int i = 0; i < MAX_X; ++i)
        for (int j = 0; j < MAX_Y; ++j)
            matrix[i][j] = ' ';
    matrix[snake.x][snake.y] = '@';

    for (int i = 0; i < (int)snake.tsize; ++i)
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';

    for (int j = 0; j < MAX_Y; ++j)
    {
        for (int i = 0; i < MAX_X; ++i)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

bool isInsideField(int x, int y)
{
    return x >= 0 && x < MAX_X - 1 && y >= 0 && y < MAX_Y - 1;
}

void generateFood(struct food f[])
{
    food->point = '$';

    for (size_t i = 0; i < SEED_NUMBER; i++)
    {
        f[i].x = rand() % (MAX_X - 2);
        f[i].y = rand() % (MAX_Y - 2) + 1;

        if (isInsideField(f[i].x, f[i].y))
        {
            printf("%c", food->point);
        }
    }
}

void refresh_Food(struct food f[], int nfood)
{
    for (size_t i = 0; (int)i < nfood; i++)
    {
        if (f[i].put_time)
        {
            if (!f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS)
            {
                generateFood(&f[i]);
            }
        }
    }
}

bool has_eaten(snake_t snake, struct food f[])
{
    for (size_t i = 0; i < MAX_FOOD_SIZE; i++)
    {
        if (f[i].enable == snake.x && snake.y == f[i].y)
        {
            f[i].enable = 0;
            return 1;
        }
    }
    return 0;
}

void addTail(snake_t *snake)
{
    if (snake->x == NULL || snake->tsize > MAX_TAIL_SIZE)
    {
        printf("You can't add the tail");
        return;
    }

    if (snake->has_eaten)
    {
        snake->tsize++;
        snake->has_eaten = false;
    }
}

void updateScreen(snake_t snake)
{
    system("cls");
    print_Snake(snake);

    if (isInsideField(snake.x, snake.y))
        generateFood(&food);
    refresh_Food(food, SEED_NUMBER);
}

void input(snake_t *snake)
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
        case 'A':
            snake->direction = LEFT; // Движение влево
            break;
        case 'd':
        case 'D':
            snake->direction = RIGHT; // Движение вправо
            break;
        case 'w':
        case 'W':
            snake->direction = UP; // Движение вверх
            break;
        case 's':
        case 'S':
            snake->direction = DOWN; // Движение вниз
            break;
        case 'q':
        case 'Q':
            printf("You are out of the game! \2\n");
            exit(EXIT_SUCCESS);
            break;
        }
    }
}

int checkDirection(struct snake_t snake, const int32_t key)
{
    if ((key == 'a' || key == 'A') && snake.direction != LEFT)
    {
        snake.direction = LEFT;
    }
    else if ((key == 'd' || key == 'D') && snake.direction != RIGHT)
    {
        snake.direction = RIGHT;
    }
    else if ((key == 'w' || key == 'W') && snake.direction != UP)
    {
        snake.direction = UP;
    }
    else if ((key == 's' || key == 'S') && snake.direction != DOWN)
    {
        snake.direction = DOWN;
    }
    return key;
}

_Bool isSnakeInTail(snake_t snake)
{
    for (size_t i = 1; i < snake.tsize; i++)
    {
        if (snake.x == snake.tail[i].x && snake.y == snake.tail[i].y)
            return 1;
    }
    return 0;
}

snake_t move_Snake(snake_t snake)
{

    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;

    if (snake.x < 0)
        snake.x = MAX_X - 1;

    if (snake.y < 0)
        snake.x = MAX_Y - 1;

    if (snake.direction == LEFT)
        --snake.x;
    else if (snake.direction == RIGHT)
        ++snake.x;
    else if (snake.direction == UP)
        --snake.y;
    else if (snake.direction == DOWN)
        ++snake.y;

    return snake;
}

int main(void)
{
    struct snake_t snake = init_Snake(10, 5, 3);
    memset(&food, 0, sizeof(food_t));

    char key = snake.direction;

    while (!GameOver)
    {
        input(&snake);
        snake = move_Snake(snake);
        checkDirection(snake, key);
        updateScreen(snake);
        sleep(1);

        if (has_eaten(snake, &food))
            addTail(&snake);

        if (isSnakeInTail(snake))
        {
            printf("You ate a tail))) Try again now.");
            GameOver = TRUE;
        }
    }
    free(snake.tail);

    return 0;
}
