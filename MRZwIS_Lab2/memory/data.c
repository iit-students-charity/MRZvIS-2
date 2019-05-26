/*******************************************************************************************
 *
 * Лабораторная работа N2 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 * 
 * Элемент памяти в модели ОКМД. Хранит в себе все матрицы и некоторые програмы
 * для выделения новой памяти под матрицы и генерации значений в матрице.
 *
 * версия 1.0
 *
 *******************************************************************************************/
#include <time.h>
#include <stdlib.h>

short** matrixA;
short** matrixB;
short** matrixC;
short*** matrixD;
short** matrixE;
short*** matrixF;
short** matrixG;
short**** TDBuffer;
short*** SBuffer;

void initSquareMatrix(matrix, x, y)
short*** matrix;
const int x;
const int y;
{
    *matrix = (short**)malloc(x * sizeof(short*));

    int i;
    int j;
    for(i = 0; i < x; i++)
    {
        *(*matrix + i) = (short*)malloc(y * sizeof(short));
    }
}

void initTriDimMatrix(matrix, x, y, z)
short**** matrix;
const int x;
const int y;
const int z;
{
    *matrix = (short***)malloc(x * sizeof(short*));

    int i;
    int j;
    for(i = 0; i < x; i++)
    {
        *(*matrix + i) = (short**)malloc(y * sizeof(short*));
        for(j = 0; j < y; j++)
        {
            *(*(*matrix + i) + j) = (short*)malloc(z * sizeof(short));
        }
    }
}

void initFourDimMatrix(matrix, v, x, y, z)
short***** matrix;
const int v;
const int x;
const int y;
const int z;
{
    *matrix = (short****)malloc(v * sizeof(short*));

    int i;
    int j;
    int k;
    for(i = 0; i < v; i++)
    {
        *(*matrix + i) = (short***)malloc(x * sizeof(short*));
        for(j = 0; j < x; j++)
        {
            *(*(*matrix + i) + j) = (short**)malloc(y * sizeof(short*));
            for(k = 0; k < y; k++)
            {
                *(*(*(*matrix + i) + j) + k) = (short*)malloc(z * sizeof(short));
            }
        }
    }
}

void delay(int numberOfMilliSeconds) 
{ 
    clock_t start_time = clock();
    while (clock() < start_time + numberOfMilliSeconds); 
}

void generateMatrix(matrix, x, y)
short*** matrix;
const int x;
const int y;
{
    initSquareMatrix(matrix, x, y);

    delay(1);
    srand(clock());

    int i;
    int j;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            *(*(*matrix + i) + j) = rand() % 3 - 1;
        }
    }
}