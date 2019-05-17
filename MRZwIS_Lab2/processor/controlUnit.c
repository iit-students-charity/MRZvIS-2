/*
Here we start and call processes.
*/
#include "processor.h"
#include "subprocessor\register.c"
//->data.c
#include "..\iounits\inputUnit.c"
#include "..\iounits\outputUnit.c"

void startProgram()
{
    outputString("Welcome in SIMDSysSim!\n");
    outputString("Input p: ");
    int p = inputInteger();
    outputString("Input m: ");
    int m = inputInteger();
    outputString("Input q: ");
    int q = inputInteger();
    matrixA = generateMatrix(p, m);
    matrixB = generateMatrix(m, q);
    matrixE = generateMatrix(1, m);
    matrixG = generateMatrix(p, q);
    callReg(SUBSTRACT, matrixA[0][0], matrixB[0][0]);
}