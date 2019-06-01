/*******************************************************************************************
 *
 * Лабораторная работа N2 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 * 
 * Элемент АЛУ в модели подпроцессора в ОКМД. Содержит в себе описания возможных операций,
 * которые способен выполнять процессор. Получает на вход адреса исходных и целевых ячеек
 * или областей в памяти. Из исходной области памяти извлекаются и обрабатываются данные.
 * Результат обработки поступает в целевую ячейку.
 *
 * версия 1.0
 *
 *******************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include "..\..\memory\data.c"

void addition(operand1, operand2, targetCell)
const short* operand1;
const short* operand2;
short* targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = op1 + op2;
    runTime += additionTime;
}

void substract(operand1, operand2, targetCell)
const short* operand1;
const short* operand2;
short* targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = op1 - op2;
    runTime += substractionTime;
}

void multiplication(operand1, operand2, targetCell)
const short* operand1;
const short* operand2;
short* targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = op1 * op2;
    runTime += multiplicationTime;
}

void isLess(operand1, operand2, targetCell)
const short* operand1;
const short* operand2;
short* targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = (op1 < op2) ? 1 : 0;
    runTime += comparationTime;
}

void waveBinAnd(operand1, operand2, targetCell)
const short* operand1;
const short* operand2;
short* targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = (op1 < op2) ? op1 : op2;
    runTime += comparationTime;
}

void waveImplication(operand1, operand2, targetCell)
const short* operand1;
const short* operand2;
short* targetCell;
{
    const short op1 = *operand1;
    const short op2 = *operand2;
    *targetCell = ((1 - op1) > op2) ? (1 - op1) : op2;
    runTime += comparationTime + substractionTime;
}

void waveUnarAnd(operand, iterationNum, targetCell)
const short** operand;
const int* iterationNum;
short* targetCell;
{
    *targetCell = 1;
    int i;
    for (i = 0; i < *iterationNum; i++)
    {
        multiplication(targetCell, (*operand + i), targetCell);
    }
}

void waveUnarOr(operand, iterationNum, targetCell)
const short** operand;
const int* iterationNum;
short* targetCell;
{
    int one = 1;
    int buffer;
    *targetCell = 1;
    int i;
    for (i = 0; i < *iterationNum; i++)
    {
        substract(&one, (*operand + i), &buffer);
        multiplication(targetCell, &buffer, targetCell);
    }
    substract(&one, targetCell, targetCell);
}