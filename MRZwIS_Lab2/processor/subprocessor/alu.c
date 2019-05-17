#include <stdbool.h>
#include "..\..\memory\data.c"
/*
 * UNARY OPERATIONS
 */
short absolute(operand) //TODO: remove absolute
short *operand;
{
    return operand < 0 ? operand * -1 : operand;
} const

short waveUnarAnd(operand)
short *operand;
{

}

short waveUnarOr(operand)
short *operand;
{
    
}
/*
 * BINARY OPERATIONS
 */
short substract(operand1, operand2)
const short *operand1;
const short *operand2;
{
    return operand1 - operand2;
}

short multiplication(operand1, operand2)
const short *operand1;
const short *operand2;
{
    return operand1 * operand2;
}

bool isLess(operand1, operand2)
const short *operand1;
const short *operand2;
{
    return operand1 < operand2 ? 1 : 0;
}

short waveBinAnd(operand1, operand2)
short *operand1;
short *operand2;
{
    return operand1 < operand2 ? operand1 : operand2;
}

short waveImplication(operand1, operand2)
short *operand1;
short *operand2;
{
    return (1 - operand1) > operand2 ? 1 - operand1 : operand2;
}