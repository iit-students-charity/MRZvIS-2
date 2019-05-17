#include "..\processor.h"
#include "alu.c"

void callReg(operation, operandPtr)
const UNARY_OPERATION_NAME operation;
const short *operandPtr;
{
    switch(operation){
        case ABSOLUTE:
            absolute();
            break;
    }
}

void callReg(operation, operand1Ptr, operand2Ptr)
const BINARY_OPERATION_NAME operation;
const short *operand1Ptr;
const short *operand2Ptr;
{
    switch(operation){
        case SUBSTRACT:
            substract(operand1Ptr, operand2Ptr);
            break;
        case IS_LESS:
            isLess(operand1Ptr, operand2Ptr);
            break;
    }
}