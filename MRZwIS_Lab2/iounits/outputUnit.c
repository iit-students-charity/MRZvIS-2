#include "io.h"

void outputString(string)
char *string;
{
    printf(string);
} const

void outputShort(number)
short *number;
{
    printf("%d", number);
} const

void outputSquareMatrix(matrixName, matrix, x, y)
char *matrixName;
short **matrix;
int x;
int y;
{
    printf("%s:\n", matrixName);
    for(int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            printf("%s[%d][%d] = %d; ", matrixName, i, j, matrix[i][j]);
        }
        printf("\n");
    }
}