
# Курсовой проект


# Итоговая работа по курсу «Программирование на языке С. "Продвинутый уровень"

### Студента - Голубева К.А.

____________________________

## Описание проекта «Система управления сельскохозяйственного дрона»:

### Требования к функционалу программы управления:
1. Дрон может перемещаться в плоскости. Перемещением дрона можно управлять
вручную.

2. Дрон может определять границы тыквенного поля, эти границы ограничивают
его перемещение.

3. Дрон может обнаруживать зрелые тыквы и собирать их в тележки для сбора.

4. Программа может отслеживать поведение целевых объектов:

    ● появление объекта на карте – обнаружение зрелой тыквы;

    ● удаление объекта с карты – зрелая тыква собрана дроном и больше не
отображается на карте;
    
    ● обновление карты – сборка урожая может происходить с некоторой
периодичностью, при обновлении карты на ней появляются новые
зрелые тыквы.
5. Программа отслеживает количество собранного урожая. Урожай собирается в
тележки, которые за собой возит дрон. Количество прикреплённых тележек для
тыкв не ограничено. При сборке тыквы длина цепочки тележек увеличивается
на 1.
6. Программа дрона уведомляет пользователя об аварийной ситуации: начало
цепочки тележек с собранными тыквами столкнулось с концом.
7. Дрон имеет режим автопилота: искусственный интеллект управляет дроном по
заданному маршруту.
8. Сборку урожая можно проводить несколькими дронами одновременно (до пяти
штук). Реализуйте кооперативный режим автопилота.


### Требования к сборке приложения:

    ● Приложение должно собираться при помощи утилиты make. (по техническим причинам не собирается make)

    ● Все прототипы функций, используемые в приложении, вынесены в отдельные файлы по функционалу: управление движением, ИИ, взаимодействие с объектами, обработка логики программы.

    ● Код программы отформатирован согласно требованиям, изученным в курсе
    «Программирование на языке С. Базовый уровень».

### Требования к оптимизации программы:

    ● Произведена оптимизация по времени (скорости) работы программы.

    ● Произведена оптимизация производительности графики: при работе
    программы не допускаются задержки изображения более 100 миллисекунд,
    и резкие перемещения объектов на экране должны быть сведены к
    минимуму, не превышая 20% от общего числа кадров в секунду.


### Критерии проверки работы:

    ● Программа работает в соответствии с требованиями ТЗ каждого
    обязательного пункта.
 
    ● Соблюдены требования к сборке программы и форматированию кода.

    ● Заполнен отчёт по работе программы.


 ###   Пояснительный раздел:
В этом разделе приведены разъяснения, как использовался проект
«Змейка», разработанный на семинарах №2, 3 и 5, для выполнения курсового
проекта. Разберём пункты с функционалом дрона-сборщика тыкв более подробно.

## Подготовка программы:

В самом начале программы происходит установка начальных значений и выделение
памяти:

● snake — голова;

● tail[] — хвост;

За это отвечают функции: init_Snake(int x, int y, size_t tsize, int color).
Голова змейки движется в соответствии с заданным направлением. Через
промежуток времени delayGame(DELAY) происходит отрисовка новой позиции головы
с учётом текущего направления. Например, если направление задано как RIGHT, то
это соответствует прибавлению 1 к текущей координате x (snake.x++). За движение
дрона (далее змейка) отвечает функция input().

1. Ручное управление
Коды управления змейкой и присвоенные клавиши хранятся в структурах.
Змейка управляется нажатием клавиш «вверх», «вниз», «вправо», «влево».
Для проверки направления движения используется функция int checkDirection(snake_t *snake, const int32_t key)

2. Сканирование и отслеживание границ
перемещения
Змейка совершает циклическое движение, что означает невозможность выхода змейки за границы терминала.
Для обеспечения данной возможности необходимо сравнить координаты головы и максимально возможное значение координаты в текущем терминале. Для
вычисления размера используется константы MAX_X, MAX_Y.
В случае, когда координата превышает максимальное значение, происходит её
обнуление.
Если координата достигает отрицательного значения, то ей присваивается
соответствующее максимальное значение MAX_X, MAX_Y.

3. Взаимодействие с объектами на поле

● объекты для взаимодействия – зрелые тыквы;

● взаимодействие – сбор тыквы в тележку для сбора.

В самом начале программы происходит установка начальных значений и выделение
памяти food.
За это отвечает функция: init_Food()
Событие сбора тыквы в тележку для сбора возникает, когда координаты головы совпадают с координатой зерна. В этом случае зерно помечается как hasEaten=1.
Проверка того, является ли какое-то из зёрен съеденным, происходит при помощи функции void updateSnakeAfterEating(snake_t *snake, food_t *food): в этом
случае происходит увеличение хвоста на 1 элемент.
Проверяется через условие if(snake->x == food->x && snake->y == food->y) происходит проверка
наличия еды и совпадения координат
В случае выполнения условий происходит:
- увеличение хвоста;
В структуре snake параметр длины tsize увеличивается на единицу. snake->tsize++;

4. Отслеживание поведения целевых объектов

● появление объекта на карте – обнаружение зрелой тыквы;

● удаление объекта с карты – зрелая тыква собрана дроном и больше не
отображается на карте;

● обновление карты – сборка урожая может происходить с некоторой
периодичностью, при обновлении карты на ней появляются новые
зрелые тыквы.

Еда — это массив точек, состоящий из координат x, y, времени, когда данная точка была установлена, и поля, сигнализирующего, была ли данная точка съедена. Точки расставляются случайным образом в самом начале программы — struct food_t init_Food().
Если через какое-то время точка устаревает, или же она
была съедена, то происходит её повторная отрисовка.

5. Отслеживание уровня заполнения тележки.

● тележка может вместить весь урожай (не переполняется), считаем
кол-во собранного урожая.

Функция void printLevel(snake_t *snake, food_t *food) позволяет считать количество урожая
(1 собранный урожай – 1 уровень).

6. Условия уведомления об аварийной ситуации.
(условия поражения змейки)

Змейка терпит поражение, когда происходит столкновение головы змейки с её хвостом. Событие возникает, когда координаты головы совпадают с координатой хвоста. Проверка того, столкнулась ли голова с хвостом, происходит при помощи функции логической функции _Bool isSnakeInTail(snake_t *snake).
В этом случае происходит автоматическое окончание игры.
При завершении игры выводится финальный результат void printExit(snake_t *snake, snake_t *snake2)

7. Режим автопилота: управление ИИ по заданному маршруту.
Для реализации автопилота, путём автоматического измнениея направления к цели
нужно добавить функцию void autoChangeDirection(snake_t *snake, food_t food). Она определяет ближайшую к себе еду и движется по
направлению к ней.

8. Кооперативный режим ИИ.

Вместо одной змеи, обрабатываем массив данных змей. snake c порядковым номером определяет количестве змей в программе.

## Описание программы:

Исходный код:

Описания файлов программы:

___________________________
//Константы границ поля

#define MAX_X 15

#define MAX_Y 15

#define START_TAIL_SIZE 2

#define MAX_TAIL_SIZE 100

#define DELAY 100

#define PAUSE 1000

#define SPEED_UP 5
_______________________________
// Константы для применения цветовой гаммы к элементам программы
#define AC_RED "\x1b[31m"

#define AC_GREEN "\x1b[32m"

#define AC_YELLOW "\x1b[33m"

#define AC_BLUE "\x1b[34m"

#define AC_MAGENTA "\x1b[35m"

#define AC_CYAN "\x1b[36m"
_____________________________

// вспомогательные нумерованные функции для задания управления

enum
{
    LEFT = 1,
    RIGHT,
    UP,
    DOWN,
    CONTROLS = 3
};
_________________________________

//Переключение между режимами игры.
!Данная функция находится на стадии реализации
enum
{
    MODE_CLASSIC,
    MODE_AI
};
char *modes[] = {"Classic_Mode", "AI_Mode"};
____________________________
//Создание струтур для элементов программы

typedef struct tail_t
{
    int x, y; 
    //координаты хвоста
} tail_t;

typedef struct food_t 
//создание еды
{
    
    int x, y; //координаты
    
    int hasEaten; //переключать при собирании еды
    int color; //применение цвета еде
} food_t;


typedef struct snake_t //структура змеи
{

    int x, y; //координаты
    int direction; //направление
    food_t food; //еда к змее
    struct tail_t *tail; //струтура хвоста связка с змеей
    size_t tsize; //размер хвоста
    int level; //уровень игры
    int speed; //скорость змеи
    int color; //цвет
} snake_t;

____________________________________
//Вспомогательные логические функции

_Bool GameOver = FALSE; //определяет состояние программы

void levelUp(snake_t *snake)//Увеличение уровня при собирании еды
{
    
    snake->level += 1;
}

void speedUp(snake_t *snake)//Увеличение скорости при собирании еды
{
    
    snake->speed -= SPEED_UP;
}

void delayGame(int ms)//Функции расчета задержки в рамках временного периода
{
    
    int startTime = clock();
    while ((clock() - startTime) < ms)
        ;
}

bool isInsideField(int x, int y)//Функция проверки нахождения в рамках границ поля
{
   
    return x >= 0 || x < MAX_X - 1 || y >= 0 || y < MAX_Y - 1;
}

_Bool isSnakeInTail(snake_t *snake)//Функция проверка стокновения змеи с хвостом
{
    
     for (size_t i = 1; i < snake->tsize; i++)
    {
        if (snake->x == snake->tail[i].x && snake->y == snake->tail[i].y)
            return 1;
    }
    return 0;
}

____________________________________

Главные функция - Логика программы:

struct snake_t
init_Snake(int x, int y, size_t tsize, int color)
// инициация элементов программы, относящихся к объекту змеи.

struct food_t init_Food() //Создание еды

void printLevel(snake_t *snake, food_t *food) //Печать текущего уровня

void printExit(snake_t *snake, snake_t *snake2) //Печать данных о состоянии программы Выигрыш/Проигрыш_Полученный уровень_МАХ

void updateSnakeAfterEating(snake_t *snake, food_t *food) //Функция для обновления данных о еде и увеличение размеров хвоста змеи после собирания еды

void pause() //Для использования паузы в программе (для отдыха/разрядки)

void autoChangeDirection(snake_t *snake, food_t food) //Создание искусственного интеллекта в программе

void startMenu() //Дает возможность настроить цветовую гамму в программе для всех её элементов

void print_Snake(struct snake_t snake, struct snake_t snake2, struct food_t food) //Функция печать для всех объектов программы

void input(snake_t *snake, snake_t *snake2) //Функция задания управления выбранной змеей (Всегда по-умолчанию WASD независимо от регистра.)

int checkDirection(snake_t *snake, const int32_t key)//Функция проверки правильности движения змеев по отношению к реальности (змея не может идти внутрь себя/)

snake_t move_Snake(snake_t snake) //Функция, которая управляет логикой поведения змеев по отношению к координатам поля

void competition(snake_t *snake, snake_t *snake2, food_t *food) //Функция запускает режим "Соревнование"

int main()||Главная функция программы, которая управляет запуском выше описанных функций и логикой поведения её элементов.

## Описание логики и характера работы программы:

Программа компилируется с помощью встроенного компилятора gcc -> далее происходит запуск функции StartMenu(), которая предлагает настроить цветовую гамму для элементов программы. После выбора цвета для всех элементов происходит запуск программы, функция print_Snake происходит отображение всех объектов на поле. Программа запрограммирована на начальное движение змеи с ручным управлением "влево". Далее программа позволяет одному пользователю выполнять управления змеёй, в соответствие с заданными параметрами в функции input(). Другая змея управляется автоматически, т.е. искусственным интеллектом, с помощью функции autoChangeDirection().
В программе необходимо выполнять сбор еды и увеличивать свой дальнейший уровень/для победы над соперником-компьютером. После проведения соревнования, пока не возникнет ситуация: столкновение со своих хвостом(тележкой) или кто-то, из участников не получит максимальный уровень, в соответствие с заданнами параметрами по константе MAX_TAIL_SIZE, которая показывает сколько звеньев хвоста (кол-во тележек)  возможно получить/собрать.
После наступления определенного события программы выдает финальный результат, с помощью функции print_Exit().

## Демонстрация работы программы: (в скриншотах)

![Стартовое меню программы](/img/1.StartMenu.JPG)

![Отображение объектов на поле](/img/2.Field&Objects.JPG)

![Вывод сведения о победителе или данных о максимальном полученном уровне](/img/3.PrintExit-Level-Wins.JPG)


