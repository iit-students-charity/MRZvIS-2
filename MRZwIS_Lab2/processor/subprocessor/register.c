#include "..\processor.h"
#include "alu.c"

void callUnarReg(operation, operandPtr, targetCellPtr)
const UNARY_OPERATION_NAME operation;
const short *operandPtr;
const short *targetCellPtr;
{
    switch(operation){
        case WAVE_UNAR_AND:
            waveUnarAnd(operandPtr, targetCellPtr);
            break;
        case WAVE_UNAR_OR:
            waveUnarOr(operandPtr, targetCellPtr);
            break;
    }
}

void callBinReg(operation, operand1Ptr, operand2Ptr, targetCellPtr)
const BINARY_OPERATION_NAME operation;
const short *operand1Ptr;
const short *operand2Ptr;
const short *targetCellPtr;
{
    switch(operation){
        case SUBSTRACT:
            substract(operand1Ptr, operand2Ptr, targetCellPtr);
            break;
        case IS_LESS:
            isLess(operand1Ptr, operand2Ptr, targetCellPtr);
            break;
        case MULTIPLICATION:
            multiplication(operand1Ptr, operand2Ptr, targetCellPtr);
            break;
        case WAVE_BIN_AND:
            waveBinAnd(operand1Ptr, operand2Ptr, targetCellPtr);
            break;
        case WAVE_IMPLICATION:
            waveImplication(operand1Ptr, operand2Ptr, targetCellPtr);
            break;
    }
}