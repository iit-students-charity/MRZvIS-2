/*******************************************************************************************
 *
 * Лабораторная работа N2 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 * 
 * Элемент регистра в модели подпроцессора в ОКМД. Обрабатывает полученные данные для 
 * последующего вызова обработчика в АЛУ.
 *
 * версия 1.0
 *
 *******************************************************************************************/
#include "..\processor.h"
#include "alu.c"

void callReg(operation, operand1Ptr, operand2Ptr, targetCellPtr)
const OPERATION_NAME operation;
const short* operand1Ptr;
const short* operand2Ptr;
const short* targetCellPtr;
{
    switch(operation){
        case ADDITION:
            addition(       operand1Ptr, operand2Ptr, targetCellPtr);
            break;
        case SUBSTRACT:
            substract(      operand1Ptr, operand2Ptr, targetCellPtr);
            break;
        case IS_LESS:
            isLess(         operand1Ptr, operand2Ptr, targetCellPtr);
            break;
        case MULTIPLICATION:
            multiplication( operand1Ptr, operand2Ptr, targetCellPtr);
            break;
        case WAVE_BIN_AND:
            waveBinAnd(     operand1Ptr, operand2Ptr, targetCellPtr);
            break;
        case WAVE_IMPLICATION:
            waveImplication(operand1Ptr, operand2Ptr, targetCellPtr);
            break;
    }
}

void callUnarReg(operation, operandPtr, digit, targetCellPtr)
const IUNAR_OPERATION_NAME operation;
const short** operandPtr;
const int* digit;
const short* targetCellPtr;
{
    switch(operation){
        case WAVE_UNAR_AND:
            waveUnarAnd(operandPtr, digit, targetCellPtr);
            break;
        case WAVE_UNAR_OR:
            waveUnarOr( operandPtr, digit, targetCellPtr);
            break;
    }
}