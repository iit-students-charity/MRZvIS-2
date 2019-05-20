#include "..\processor.h"
#include "alu.c"

void callUnarReg(operation, operandPtr)
const UNARY_OPERATION_NAME operation;
const short *operandPtr;
{
    switch(operation){
        case WAVE_UNAR_AND:
            waveUnarAnd(operandPtr);
            break;
        case WAVE_UNAR_OR:
            waveUnarOr(operandPtr);
            break;
    }
} const

void callBinReg(operation, operand1Ptr, operand2Ptr)
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
        case MULTIPLICATION:
            multiplication(operand1Ptr, operand2Ptr);
            break;
        case WAVE_BIN_AND:
            waveBinAnd(operand1Ptr, operand2Ptr);
            break;
        case WAVE_IMPLICATION:
            waveImplication(operand1Ptr, operand2Ptr);
            break;
    }
} const