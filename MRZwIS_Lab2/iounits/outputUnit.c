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
    printf("matrix %s:\n", matrixName);
    for(int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            printf("%s[%d][%d] = %d; \t", matrixName, i, j, matrix[i][j]);
        }
        printf("\n");
    }
}

void outputTriDimMatrix(matrixName, matrix, x, y, z)
char *matrixName;
short ***matrix;
int x;
int y;
int z;
{
    printf("matrix %s:\n", matrixName);
    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                printf("%s[%d][%d][%d] = %d;  \t", matrixName, i, j, k, matrixD[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}