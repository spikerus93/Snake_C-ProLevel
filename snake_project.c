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

homework5
Задача 1. Цвет змеек
Домашнее задание
Добавить цвет для двух змеек и еды.

Задание 2. Стартовое меню
Добавить стартовое меню (приветствие, выбор режима, выбор цвета змейки и т.д.).
Написать функцию void startMenu().

*Задание 3. Исполняемый файл
Попробовать внести изменения в исполняемый файл, чтобы в стандартном режиме змейка не погибала при самопересечении.
Для этого необходимо найти вызов функции isCrush() и поменять вызов на нужное нам возвращаемое значение 0.

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

struct snake_t
init_Snake(int x, int y, size_t tsize, int color)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100 * MAX_TAIL_SIZE);
    snake.direction = 1;
    snake.level = 1;
    snake.speed = DELAY;
    snake.color = color;

    for (int i = 0; i < (int)tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

struct food_t init_Food()
{
    struct food_t food;

    food.x = rand() % MAX_X;
    food.y = rand() % MAX_Y;

    food.hasEaten = 0;

    return food;
}

void levelUp(snake_t *snake)
{
    snake->level += 1;
}

void printLevel(snake_t *snake, food_t *food)
{
    for (int i = 0; i < 2; i++)
    {
        if (snake[i].x == food->x && snake[i].y == food->y)
        {
            snake[i].level++;
            printf("Level UP!: %d\n", snake[i].level);
        }
    }
}

void printExit(snake_t *snake, snake_t *snake2)
{
    if (snake->level > snake2->level)
    {
        printf("Snake 1 wins!\n");
    }
    else
    {
        printf("Snake 2 wins!\n");
    }
    printf("Final Level: %d\n", snake->level);
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

void updateSnakeAfterEating(snake_t *snake, food_t *food)
{
    if (snake->x == food->x && snake->y == food->y)
    {
        food->hasEaten = 1;
        snake->tsize++;
        speedUp(snake);
        levelUp(snake);
    }
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

void autoChangeDirection(snake_t *snake, food_t food)
{
    if ((snake->direction == LEFT || snake->direction == RIGHT) && snake->y == food.y)
        return;

    if ((snake->direction == LEFT || snake->direction == RIGHT) && snake->y != food.y)
    {
        if (food.x == snake->x)
        {
            if (abs(food.y - snake->y) <= MAX_Y / 2)
            {
                snake->direction = food.y - snake->y > 0 ? UP : DOWN;
            }
            else
            {
                snake->direction = food.y - snake->y > 0 ? DOWN : UP;
            }
        }
        return;
    }

    if ((snake->direction == UP || snake->direction == DOWN) && snake->x == food.x)
        return;

    if ((snake->direction == UP || snake->direction == DOWN) && snake->x != food.x)
    {
        if (snake->y == food.y)
        {
            if (abs(food.x - snake->x) <= MAX_X / 2)
            {
                snake->direction = food.x - snake->x > 0 ? RIGHT : LEFT;
            }
            else
            {
                snake->direction = food.x - snake->x > 0 ? LEFT : RIGHT;
            }
        }
        return;
    }
}

void startMenu()
{
    snake_t snake;
    snake_t snake2;
    food_t food;

    printf("Welcome to Snake Game!\n");

    printf("Choose a color (Num = '1' till '6') for your snakes and food:\n");

    int colorChoice;
    int colorCount = 0;
    bool differentColorsFound = false;

    do
    {
        printf("Color: ");
        scanf("%d", &colorChoice);

        if (colorChoice < 1 || colorChoice > 6)
            printf("Invalid color. Please try again.\n");
        else
            switch (colorChoice)
            {
            case 1:
                printf("%s\n", AC_RED);
                break;
            case 2:
                printf("%s\n", AC_GREEN);
                break;
            case 3:
                printf("%s\n", AC_YELLOW);
                break;
            case 4:
                printf("%s\n", AC_BLUE);
                break;
            case 5:
                printf("%s\n", AC_MAGENTA);
                break;
            case 6:
                printf("%s\n", AC_CYAN);
                break;
            }

        if (!differentColorsFound)
        {
            colorCount++;
            snake.color = colorChoice;
        }
        else if (!differentColorsFound)
        {
            colorCount++;
            snake2.color = colorChoice;
        }
        else
        {
            colorCount++;
            food.color = colorChoice;
            differentColorsFound = true;
        }
    } while (colorCount < 3 && !differentColorsFound);

    printf("Starting game with color %d, %d, %d\n", snake.color, snake2.color, food.color);
}

void print_Snake(struct snake_t snake, struct snake_t snake2, struct food_t food)
{
    char matrix[MAX_X][MAX_Y];

    for (int i = 0; i < MAX_X; ++i)
        for (int j = 0; j < MAX_Y; ++j)
            matrix[i][j] = ' ';

    matrix[food.x][food.y] = '$';
    matrix[snake.x][snake.y] = '@';
    matrix[snake2.x][snake2.y] = '%';

    for (int i = 0; i < (int)snake.tsize; ++i)
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';

    for (int i = 0; i < (int)snake2.tsize; ++i)
        matrix[snake2.tail[i].x][snake2.tail[i].y] = '-';

    for (int j = 0; j < MAX_Y; ++j)
    {
        for (int i = 0; i < MAX_X; ++i)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

void input(snake_t *snake, snake_t *snake2)
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
        case 'A':
            if (snake->direction == RIGHT)
                break;
            snake->direction = LEFT; // Змейка1 = Движение влево
            break;
        case 'd':
        case 'D':
            if (snake->direction == LEFT)
                break;
            snake->direction = RIGHT; // Змейка1 = Движение вправо
            break;
        case 'w':
        case 'W':
            if (snake->direction == DOWN)
                break;
            snake->direction = UP; // Змейка1 = Движение вверх
            break;
        case 's':
        case 'S':
            if (snake->direction == UP)
                break;
            snake->direction = DOWN; // Змейка1 = Движение вниз
            break;

        case 'q':
        case 'Q':
            printf("\nYou are out of the game!\n");
            printExit(snake, snake2);
            exit(EXIT_SUCCESS);
            break;
        case 'p':
        case 'P':
            pause();
            break;
        }
    }
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

int checkDirection(snake_t *snake, const int32_t key)
{
    if ((snake->direction == LEFT && (key == 'd' || key == 'D') && (key == 'l' || key == 'L')) ||
        (snake->direction == RIGHT && (key == 'a' || key == 'A') && (key == 'j' || key == 'J')) ||
        (snake->direction == UP && (key == 's' || key == 'S') && (key == 'k' || key == 'K')) ||
        (snake->direction == DOWN && (key == 'w' || key == 'W') && (key == 'i' || key == 'I')))
    {
        return 0;
    }
    return 1;
}

snake_t move_Snake(snake_t snake)
{

    for (int i = snake.tsize; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;

    if (snake.x < 0)
        snake.x = MAX_X - 1;

    if (snake.x == MAX_X)
        snake.x = 0;

    if (snake.y == MAX_Y)
        snake.y = 0;

    if (snake.y < 0)
        snake.y = MAX_Y - 1;

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

void competition(snake_t *snake, snake_t *snake2, food_t *food)
{
    if (snake->x == food->x && snake->y == food->y)
    {
        updateSnakeAfterEating(snake, food);
        printLevel(snake, food);
    }

    if (snake2->x == food->x && snake2->y == food->y)
    {
        updateSnakeAfterEating(snake2, food);
        printLevel(snake, food);
    }

    // Определяем победителя на основе длины змеи
    if (snake->tsize > snake2->tsize || snake->tsize == MAX_TAIL_SIZE)
    {
        printf("Snake 1 wins!\n");
    }
    else if (snake2->tsize > snake->tsize || snake2->tsize == MAX_TAIL_SIZE)
    {
        printf("Snake 2 wins!\n");
    }
    else
    {
        // Длины равны, определяем победителя по уровню сложности
        if (snake->level > snake2->level)
        {
            printf("Snake 1 wins!\n");
            printExit(snake, snake2);
        }
        else if (snake2->level > snake->level)
        {
            printf("Snake 2 wins!\n");
            printExit(snake, snake2);
        }
        else if (GameOver)
        {
            if ((snake->tsize == snake2->tsize) || snake->level == snake2->level)
            {
                // Все остальные случаи остаются ничьей
                printf("It's a draw!\n");
                printExit(snake, snake2);
            }
        }
    }
}

int main(void)
{

    struct snake_t snake = init_Snake(10, 5, 2, snake.color);
    struct snake_t snake2 = init_Snake(5, 2, 2, snake2.color);

    food_t food = init_Food();

    startMenu();
    print_Snake(snake, snake2, food);

    int key = snake.direction;

    while (!GameOver)
    {
        srand(time(NULL));

        input(&snake, &snake2);
        autoChangeDirection(&snake2, food);
        snake = move_Snake(snake);
        snake2 = move_Snake(snake2);
        competition(&snake, &snake2, &food);
        updateSnakeAfterEating(&snake, &food);
        updateSnakeAfterEating(&snake2, &food);
        printLevel(&snake, &food);
        printLevel(&snake2, &food);
        checkDirection(&snake, key);

        if (food.hasEaten)
        {
            food = init_Food();
        }

        if (isSnakeInTail(&snake) && isSnakeInTail(&snake2) && !isInsideField(snake.x, snake.y) && !isInsideField(snake2.x, snake2.y))
        {
            printf("You ate a tail))) Try again now.");
            GameOver = TRUE;
            break;
        }
        sleep(0.95);
        system("cls");
        print_Snake(snake, snake2, food);
        delayGame(snake.speed);
    }
    free(snake.tail);
    free(snake2.tail);

    return 0;
}
