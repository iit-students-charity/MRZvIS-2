/*
 * Just stores all data
 * Получить построенную модель ОКМД архитектуры, реализующего решение варианта задачи вычисления 
 * матрицы значений, обеспечивающую возможность параметрического задания 
 * - времени счёта (длины) операций различных типов ti (сложение, разность, произведение, деление, сравнение и др.); 
 * - наборы входных данных должны генерироваться; 
 * 
 * Дано:
 * A(pxm), B(mxq), E(1xm), G(pxq)
 * i = p, j = q, k = m
 * C(i,j), F(ixjxk), D(ixjxk)
 * 
 * Сделать стак результатов вычислений?
 */
#include <time.h>
#include <stdlib.h>

short **matrix;
short **matrixA;
short **matrixB;
short **matrixC;
short ***matrixD;
short **matrixE;
short ***matrixF;
short **matrixG;

void delay(int numberOfMilliSeconds) 
{ 
    clock_t start_time = clock();
    while (clock() < start_time + numberOfMilliSeconds); 
}

short **generateMatrix(matrix, x, y)
short **matrix;
const int x;
const int y;
{
    delay(1);
    srand(time(NULL));

    initSquareMatrix(matrix, x, y);

    int i;
    int j;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            *(*(matrix + i) + j) = rand() % 3 - 1;
        }
    }
    return matrix;
}

void initSquareMatrix(matrix, x, y)
short **matrix;
const int x;
const int y;
{
    matrix = (short**)malloc(x * sizeof(short*));

    int i;
    for(i = 0; i < x; i++)
    {
        *(matrix + i) = (short*)malloc(y * sizeof(short));
    }
}

void initTriDimMatrix(matrix, x, y, z)
short ***matrix;
const int x;
const int y;
const int z;
{
    matrix = (short***)malloc(x * sizeof(short*));

    int i;
    int j;
    for(i = 0; i < x; i++)
    {
        *(matrix + i) = (short**)malloc(y * sizeof(short*));
        for(j = 0; j < y; j++)
        {
            *(*(matrix + i) + j) = (short*)malloc(z * sizeof(short));
        }
    }
}