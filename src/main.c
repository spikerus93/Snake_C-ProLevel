#include <snake_project.c>

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