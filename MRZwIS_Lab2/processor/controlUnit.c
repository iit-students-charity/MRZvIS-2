/*
Here we start and call processes.

Внутри смих вычислений целевых матриц мжно создавать списки результатов.
*/
#include "processor.h"
#include "procBus.c"
#include "..\iounits\inputUnit.c"
#include "..\iounits\outputUnit.c"

void generateInitialMatrixes(p, m, q)
const int p;
const int m;
const int q;
{
    generateMatrix(matrixA, p, m);
    generateMatrix(matrixB, m, q);
    generateMatrix(matrixE, 1, m);
    generateMatrix(matrixG, p, q);
}

void calculateMatrixD(p, m, q)
const int p;
const int m;
const int q;
{
    initTriDimMatrix(matrixD, p, m, q);
    iterate3Bin_SMxSM(WAVE_BIN_AND, matrixA, matrixB, p, m, q, matrixD);
}

void calculateMatrixF(p, m, q)
const int p;
const int m;
const int q;
{
    const int SUBEXPRESSION_COUNT    = 2;
    const int SUBSUBEXPRESSION_COUNT = 7;
    short **subexpressionList = (short**)malloc(SUBEXPRESSION_COUNT * sizeof(short*));
    int i;
    for(i = 0; i < SUBEXPRESSION_COUNT; i++)
    {
        subexpressionList[i] = (short*)malloc(SUBSUBEXPRESSION_COUNT * sizeof(short));
    }
    release(i);

    matrixF = (short***)malloc(p * sizeof(short*));
    int i;
    int j;
    int k;
    for(i = 0; i < p; i++)
    {
        matrixF[i] = (short**)malloc(q * sizeof(short*));
        for(j = 0; j < q; j++)
        {
            matrixF[i][j] = (short*)malloc(k * sizeof(short));
            for(k = 0; k < m; k++)
            {
                waveImplication(&matrixA[i][k], &matrixB[k][j], &subexpressionList);

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
    outputString("Calculating D matrix...\n");
    calculateMatrixD(p, m, q);
    outputString("D matrix calculated!\n");
    outputTriDimMatrix("D", matrixD, p, m, q);

    outputString("Calculating F matrix...\n");
    calculateMatrixD(p, m, q);
    outputString("F matrix calculated!\n");
    outputTriDimMatrix("F", matrixF, p, m, q);
    outputString("Target matrixes successfuly calculated!\n");

    outputString("Program successfuly completed!\n");
}