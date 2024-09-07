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
Для решения предлагается сделать массив кодов управления struct control_buttons
default_controls[CONTROLS]. CONTROLS – определяем количество элементов массива.
В необходимых функциях в цикле необходимо сравнивать с каждым типом управления в цикле
for (int i = 0; i < CONTROLS; i++)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>

#define MAX_X 15
#define MAX_Y 15
#define MIN_Y 2

enum
{
    LEFT = 1,
    RIGHT,
    UP,
    DOWN,
    STOP_GAME = VK_F10,
    CONTROLS = 3
};

struct control_buttons
{
    int left, right, up, down;
} controls_buttons;

struct control_buttons default_controls[CONTROLS] =
    {{LEFT, RIGHT, UP, DOWN},
     {'a', 'd', 'w', 's'},
     {'A', 'D', 'W', 'S'}};

typedef struct tail_t
{
    int x, y;
} tail_t;

typedef struct snake_t
{
    int x, y;
    int direction;
    struct tail_t *tail;
    size_t tsize;
    struct control_buttons *controls;
} snake_t;

_Bool GameOver = FALSE;

struct snake_t
init_Snake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    snake.controls = default_controls;
    snake.direction = LEFT;

    for (int i = 0; i < (int)tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
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

int changeDirection(struct snake_t snake, const int32_t key)
{
    if (key == 'a' || key == 'A')
    {
        if (snake.controls->left != 0)
            snake.controls->left = 0;
        else
            snake.controls->left = 1;
    }

    if (key == 'd' || key == 'D')
    {
        if (snake.controls->right != 0)
            snake.controls->right = 0;
        else
            snake.controls->right = 1;
    }

    if (key == 'w' || key == 'W')
    {
        if (snake.controls->up != 0)
            snake.controls->up = 0;
        else
            snake.controls->up = 1;
    }

    if (key == 's' || key == 'S')
    {
        if (snake.controls->down != 0)
            snake.controls->down = 0;
        else
            snake.controls->down = 1;
    }
    return key;
}

int get_direction(snake_t snake)
{
    int current_direction = snake.direction;

    if (snake.controls->left == 1)
    {
        current_direction = LEFT;
        return TRUE;
    }

    else if (snake.controls->right == 1)
    {
        current_direction = RIGHT;
        return TRUE;
    }

    else if (snake.controls->up == 1)
    {
        current_direction = UP;
        return TRUE;
    }

    else if (snake.controls->down == 1)
    {
        current_direction = DOWN;
        return TRUE;
    }
    else
        return FALSE;
    return current_direction;
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

snake_t move_Snake(snake_t snake, const int32_t key)
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

    if (_kbhit())
    {
        snake.direction = getch();
        switch (key)
        {
        case LEFT:
            --snake.x;
            break;
        case RIGHT:
            ++snake.x;
            break;
        case UP:
            --snake.y;
            break;
        case DOWN:
            ++snake.y;
            break;
        }
    }
    return snake;
}

int main(void)
{
    struct snake_t snake = init_Snake(10, 5, 3);

    while (!GameOver)
    {
        char key = _getch();

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

        snake = move_Snake(snake, key);
        changeDirection(snake, key);
        get_direction(snake);

        system("cls");
        print_Snake(snake);
        sleep(1);

        if (isSnakeInTail(snake))
        {
            GameOver = TRUE;
        }
    }

    free(snake.tail);

    return 0;
}
