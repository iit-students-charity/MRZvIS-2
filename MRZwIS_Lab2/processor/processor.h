/*******************************************************************************************
 *
 * Лабораторная работа N2 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 * 
 * Заголовочный файл, используемый файлами с кодом, описывающим работу процессора
 * эмулируемой машины.
 *
 * версия 1.0
 *
 *******************************************************************************************/
#ifndef SIMD_PROCESSOR_H
#define SIMD_PROCESSOR_H

int subprocCount = 4;

#define IUNAR_OPERATION_NAME enum iterativeUnaryOperationName
IUNAR_OPERATION_NAME
{
    WAVE_UNAR_AND, WAVE_UNAR_OR
};
#define OPERATION_NAME enum binaryOperationName
OPERATION_NAME
{
    ADDITION, SUBSTRACT, MULTIPLICATION, IS_LESS, WAVE_BIN_AND, WAVE_IMPLICATION
};
#define MATR_NAME enum matrixName
MATR_NAME
{
    A, B, C, D, E, F
};

#endif // SIMD_PROCESSOR_H