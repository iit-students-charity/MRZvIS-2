#include <stdbool.h>
#include <stdio.h> //TODO: remove
#include "..\..\memory\data.c"
/*
 * UNARY OPERATIONS
 */
void waveUnarAnd(operand, targetCell)
short **operand;
short *targetCell;
{
    //Можно сделать увелчением последней калькуляции, а сюда передавать только на сколько увеличение делать
    *targetCell = 1;
    int i;
    for (i = 0; i < sizeof(operand)/sizeof(short*); i++)
    {
        *targetCell *= *(*(operand + i));
    }
}

void waveUnarOr(operand, targetCell)
short **operand;
short *targetCell;
{
    *targetCell = 1;
    int i;
    for (i = 0; i < sizeof(operand)/sizeof(short*); i++)
    {
        *targetCell *= 1 - *(*(operand + i));
    }
    *targetCell = 1 - *targetCell;
}
/*
 * BINARY OPERATIONS
 */
void substract(operand1, operand2, targetCell)
const short *operand1;
const short *operand2;
short *targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = op1 - op2;
}

void multiplication(operand1, operand2, targetCell)
const short *operand1;
const short *operand2;
short *targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = op1 * op2;
}

void isLess(operand1, operand2, targetCell)
const short *operand1;
const short *operand2;
short *targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = op1 < op2 ? 1 : 0;
}

void waveBinAnd(operand1, operand2, targetCell)
const short *operand1;
const short *operand2;
short *targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = op1 < op2 ? op1 : op2;
}

void waveImplication(operand1, operand2, targetCell)
const short *operand1;
const short *operand2;
short *targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = (1 - op1) > op2 ? 1 - op1 : op2;
}