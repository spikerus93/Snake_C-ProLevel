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

#define START_TAIL_SIZE 2
#define MAX_TAIL_SIZE 100

#define DELAY 100
#define PAUSE 1000
#define SPEED_UP 5

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
    int hasEaten;
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
} snake_t;

_Bool GameOver = FALSE;

struct snake_t
init_Snake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100 * MAX_TAIL_SIZE);
    snake.direction = 1;
    snake.level = 1;
    snake.speed = DELAY;

    for (int i = 0; i < (int)tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

food_t init_Food()
{
    food_t food;
    food.x = rand() % MAX_X;
    food.y = rand() % MAX_Y;
    food.hasEaten = 0;
    return food;
}

void speedUp(snake_t *snake)
{
    snake->speed -= SPEED_UP;
}

void printLevel(snake_t *snake)
{
    printf("Level: %d\n", snake->level);
}

void printExit(snake_t *snake)
{
    printf("Game Over!\n");
    printf("Final Level: %d\n", snake->level);
}

void delayGame(int ms)
{
    int startTime = clock();
    while ((clock() - startTime) < ms)
        ;
}

void pause()
{
    int ch;

    do
    {
        ch = _getch();
    } while (ch != 'p' && ch != 'P');
    printf("PAUSE\n");
    delayGame(PAUSE);
}

void print_Snake(struct snake_t snake, struct food_t food)
{
    char matrix[MAX_X][MAX_Y];

    for (int i = 0; i < MAX_X; ++i)
        for (int j = 0; j < MAX_Y; ++j)
            matrix[i][j] = ' ';

    matrix[food.x][food.y] = '$';
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

void input(snake_t *snake)
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
        case 'A':
            if (snake->direction == RIGHT)
                break;
            snake->direction = LEFT; // Движение влево
            break;
        case 'd':
        case 'D':
            if (snake->direction == LEFT)
                break;
            snake->direction = RIGHT; // Движение вправо
            break;
        case 'w':
        case 'W':
            if (snake->direction == DOWN)
                break;
            snake->direction = UP; // Движение вверх
            break;
        case 's':
        case 'S':
            if (snake->direction == UP)
                break;
            snake->direction = DOWN; // Движение вниз
            break;
        case 'q':
        case 'Q':
            printExit(snake);
            exit(EXIT_SUCCESS);
            break;
        case 'p':
        case 'P':
            pause();
            break;
        }
    }
}

_Bool isSnakeInTail(snake_t snake)
{
    for (size_t i = 0; i < snake.tsize; i++)
    {
        if (snake.x == snake.tail[i].x || snake.y == snake.tail[i].y)
            return 0;
    }
    return 1;
}

int checkDirection(snake_t *snake, const int32_t key)
{
    if ((snake->direction == LEFT && (key == 'd' || key == 'D')) ||
        (snake->direction == RIGHT && (key == 'a' || key == 'A')) ||
        (snake->direction == UP && (key == 's' || key == 'S')) ||
        (snake->direction == DOWN && (key == 'w' || key == 'W')))
    {
        return 0;
    }
    return 1;
}

snake_t movetoEat_Snake(snake_t snake, food_t *food)
{

    for (int i = snake.tsize - 1; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;

    if (snake.x < 0)
        snake.x = MAX_X - 1;

    if (snake.x == MAX_X)
        snake.x = 0;

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

    if (snake.x == food->x && snake.y == food->y)
    {
        food->hasEaten = 1;
        snake.tsize++;
        speedUp(&snake);
        snake.level++;
        printLevel(&snake);
    }
    return snake;
}

int main(void)
{
    struct snake_t snake = init_Snake(10, 5, 2);
    food_t food = init_Food();
    print_Snake(snake, food);

    int key = snake.direction;

    while (!GameOver)
    {
        input(&snake);
        snake = movetoEat_Snake(snake, &food);
        checkDirection(&snake, key);

        if (checkDirection(&snake, key) == 0)
        {
            return 0;
        }
        else
        {
            if (food.hasEaten)
                food = init_Food();
        }

        if (isSnakeInTail(snake))
        {
            printf("You ate a tail))) Try again now.");
            GameOver = TRUE;
            break;
        }

        sleep(0.9);
        system("cls");
        print_Snake(snake, food);
        delayGame(snake.speed);
    }
    free(snake.tail);

    return 0;
}
