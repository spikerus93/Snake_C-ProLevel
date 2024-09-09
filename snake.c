#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

#define MAX_X 15
#define MAX_Y 15

typedef struct Tail
{
    int x, y;
} Tail;

typedef struct Snake
{
    int dir_x, dir_y;
    int next_dir_x, next_dir_y;
    int lenght;
    int pos_x;
    int pos_y;

    bool change_dir;
} Snake;

typedef struct SnakeNode
{
    __INT32_TYPE__ lifetime;
} SnakeNode;

bool game_over = false;

Snake snake;
SnakeNode snake_body[MAX_X][MAX_Y];

void InitSnake()
{
    for (int i = 0; i < snake.lenght; i++)
    {
        int x = snake.pos_x - snake.dir_x * i;
        int y = snake.pos_y - snake.dir_y * i;
        snake_body[x][y].lifetime = snake.lenght - i;
    }
}

// void print_Snake(snake)
// {
//     char body[MAX_X][MAX_Y];

//     for (int i = 0; i < MAX_X; i++)
//     {
//         for (int j = 0; i < MAX_Y; j++)
//         {
//             body[i][j] = ' ';
//         }
//     }
//     body[snake.pos_x*i][snake.pos_y*j]
// }

void CheckInTail()
{
    if (snake_body[snake.pos_x][snake.pos_y].lifetime > 0)
    {
        game_over = true;
    }
}

void CheckInWall()
{
    if (snake_body[snake.pos_x][snake.pos_y].lifetime > 0)
    {
        game_over = true;
    }
}

void MoveSnake()
{
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            if (snake_body[i][j].lifetime > 0)
            {
                snake_body[i][j].lifetime--;
            }
        }
    }
    snake.dir_x = snake.next_dir_x;
    snake.dir_y = snake.next_dir_y;
    snake.pos_x += snake.dir_x;
    snake.pos_y += snake.dir_y;

    if (snake.pos_x >= MAX_X)
    {
        snake.pos_x = 0;
    }
    if (snake.pos_x < 0)
    {
        snake.pos_x = MAX_X - 1;
    }
    if (snake.pos_y >= MAX_Y)
    {
        snake.pos_y = 0;
    }
    if (snake.pos_y < 0)
    {
        snake.pos_y = MAX_Y - 1;
    }

    CheckInTail();
    CheckInWall();
    snake_body[snake.pos_x][snake.pos_y].lifetime = snake.lenght;
}

void Controls()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
        case 'W':
            snake.next_dir_y = -1;
            snake.next_dir_x = 0;
            break;
        case 's':
        case 'S':
            snake.next_dir_y = 1;
            snake.next_dir_x = 0;
            break;
        case 'a':
        case 'A':
            snake.next_dir_y = 0;
            snake.next_dir_x = -1;
            break;
        case 'd':
        case 'D':
            snake.next_dir_y = 0;
            snake.next_dir_x = 1;
            break;
        }
    }
}

int main()
{
    Controls();
    InitSnake();
    MoveSnake();
}