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

short **matrixA;
short **matrixB;
short **matrixC;
short ***matrixD;
short **matrixE;
short ***matrixF;
short **matrixG;

short **generateMatrix(x, y)
const int x;
const int y;
{
    short **matrix;
    srand(time(NULL));
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            matrix[i][j] = rand() % 3 - 1;
        }
    }
    return matrix;
} const