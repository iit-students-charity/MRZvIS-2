/*
Here we start and call processes.

Внутри смих вычислений целевых матриц мжно создавать списки результатов.
*/
#include "processor.h"
#include "subprocessor\register.c"
//->data.c
#include "..\iounits\inputUnit.c"
#include "..\iounits\outputUnit.c"

void generateInitialMatrixes(p, m, q)
const int p;
const int m;
const int q;
{
    //выделение памяти сюда?неееееееееееееееееееееее
    matrixA = generateMatrix(p, m);
    matrixB = generateMatrix(m, q);
    matrixE = generateMatrix(1, m);
    matrixG = generateMatrix(p, q);
}

void calculateMatrixD(p, m, q)
const int p;
const int m;
const int q;
{
    matrixD = (short***)malloc(p * sizeof(short*));
    int i;
    int j;
    int k;
    for(i = 0; i < p; i++)
    {
        matrixD[i] = (short**)malloc(q * sizeof(short*));
        for(j = 0; j < q; j++)
        {
            matrixD[j] = (short*)malloc(k * sizeof(short));
            for(k = 0; k < m; k)
            {
                waveBinAnd(matrixA[i][k], matrixB[k][j]);
                matrixD[i][j][k] = lastCalculation;
                outputShort(matrixD[i][j][k]);
            }
        }
    }
}

void startProgram()
{
    outputString("Welcome in SIMDSysSim!\n");

    outputString("Input subprocessor count: ");
    int subprocCount = inputInteger();

    outputString("Starting a program...\n");

    outputString("Input p: ");
    int p = inputInteger();
    outputString("Input m: ");
    int m = inputInteger();
    outputString("Input q: ");
    int q = inputInteger();

    outputString("Generating initial matrixes...\n");
    generateInitialMatrixes(p, m, q);
    outputString("Initial matrixes successfuly generated!\n");
    outputSquareMatrix("A", matrixA, p, m);
    outputSquareMatrix("B", matrixB, m, q);
    outputSquareMatrix("E", matrixE, 1, m);
    outputSquareMatrix("G", matrixG, p, q);

    outputString("Would you like to start target matrixes calculation?(input anything to agree)");
    inputInteger();

    outputString("Calculating target matrixes...\n");
    calculateMatrixD(p, m, q);
    outputString("Target matrixs successfuly calculated!\n");

    outputString("Program successfuly completed!\n");
}