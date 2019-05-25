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
    generateMatrix(&matrixA, p, m);
    generateMatrix(&matrixB, m, q);
    generateMatrix(&matrixE, 1, m);
    generateMatrix(&matrixG, p, q);
}

void calculateMatrixD(p, m, q)
const int p;
const int m;
const int q;
{
    initTriDimMatrix(&matrixD, p, m, q);
    iterate3Bin_SMxSM(WAVE_BIN_AND, &matrixA, &matrixB, p, m, q, &matrixD);
}

void calculateMatrixF(p, m, q)
const int p;
const int m;
const int q;
{
    const int SUBEXPRESSION_LEVELS_COUNT = 3;

    initTriDimMatrix(&matrixF, p, m, q);
    initFourDimMatrix(TDBuffer, SUBEXPRESSION_LEVELS_COUNT, p, m, q);

    iterate3Bin_SMxSM(WAVE_IMPLICATION, &matrixA, &matrixB, p, m, q, &TDBuffer[1]);
    iterate3Bin_UMxD(MULTIPLICATION, &matrixE[1], 2, p, m, q, &TDBuffer[2]);
    iterate3Bin_UMxD(SUBSTRACT, &TDBuffer[2][1][1], 1, p, m, q, &TDBuffer[2]);
    iterate3Bin_TDMxTDM(MULTIPLICATION, &TDBuffer[1], &TDBuffer[2], p, m, q, &TDBuffer[1]);
    iterate3Bin_TDMxUM(MULTIPLICATION, &TDBuffer[1], &matrixE[1], p, m, q, &TDBuffer[1]);
    TDBuffer[0] = TDBuffer[1];
    iterate3Bin_SMxSM(WAVE_IMPLICATION, &matrixB, &matrixA, p, m, q, &TDBuffer[1]);
    iterate3Bin_SMxSM(WAVE_IMPLICATION, &matrixA, &matrixB, p, m, q, &TDBuffer[2]);
    iterate3Bin_TDMxD(MULTIPLICATION, &TDBuffer[2], 4, p, m, q, &TDBuffer[2]);
    matrixF = TDBuffer[0];
}

void startProgram()
{
    outputString("Welcome in SIMDSysSim!\n");

    outputString("Input subprocessor count: ");
    subprocCount = inputInteger();

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

    outputSquareMatrix("A", &matrixA, p, m);
    outputSquareMatrix("B", &matrixB, m, q);
    outputSquareMatrix("E", &matrixE, 1, m);
    outputSquareMatrix("G", &matrixG, p, q);

    outputString("Calculating target matrixes...\n");

    outputString("Would you like to calculate D matrix?(input anything to agree)");
    inputInteger();

    outputString("Calculating D matrix...\n");
    calculateMatrixD(p, m, q);
    outputString("D matrix calculated!\n");
    outputTriDimMatrix("D", &matrixD, p, m, q);

    outputString("Would you like to calculate F matrix?(input anything to agree)");
    inputInteger();

    outputString("Calculating F matrix...\n");
    calculateMatrixF(p, m, q);
    outputString("F matrix calculated!\n");
    outputTriDimMatrix("F", &matrixF, p, m, q);
    outputString("Target matrixes successfuly calculated!\n");

    outputString("Program successfuly completed!\n");
}