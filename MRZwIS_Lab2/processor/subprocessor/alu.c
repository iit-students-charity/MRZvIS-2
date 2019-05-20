#include <stdbool.h>
#include <stdio.h>
#include "..\..\memory\data.c"
/*
 * UNARY OPERATIONS
 */
void waveUnarAnd(operand)
short *operand;
{
    lastCalculation = 1;
    int i;
    for (i = 0; i < sizeof(operand)/sizeof(short); i++)
    {
        lastCalculation *= operand[i];
    }
}

void waveUnarOr(operand)
short *operand;
{
    lastCalculation = 1;
    int i;
    for (i = 0; i < sizeof(operand)/sizeof(short); i++)
    {
        lastCalculation *= 1 - operand[i];
    }
    lastCalculation = 1 - lastCalculation;
}
/*
 * BINARY OPERATIONS
 */
void substract(operand1, operand2)
const short *operand1;
const short *operand2;
{
    lastCalculation = operand1 - operand2;
}

void multiplication(operand1, operand2)
const short *operand1;
const short *operand2;
{
    const short op1 = operand1;
    const short op2 = operand2;
    lastCalculation = op1 * op2;
}

void isLess(operand1, operand2)
const short *operand1;
const short *operand2;
{
    lastCalculation = operand1 < operand2 ? 1 : 0;
}

void waveBinAnd(operand1, operand2)
const short *operand1;
const short *operand2;
{
    lastCalculation = operand1 < operand2 ? operand1 : operand2;
}

void waveImplication(operand1, operand2)
const short *operand1;
const short *operand2;
{
    const short op1 = operand1;
    const short op2 = operand2;
    lastCalculation = (1 - op1) > op2 ? 1 - op1 : op2;
}