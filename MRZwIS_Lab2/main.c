/*******************************************************************************************
 *
 * Лабораторная работа N2 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 * 
 * Система представляет собой эмуляцию машины с процессором на ОКМД архитектуре.
 *
 * Главная функция програмы, выводящая диалог ввода количества подпроцессоров и запускающая
 * програму для рассчёта матриц.
 *
 * Создано с использованием технологии языка C98
 *
 * версия 1.0
 *
 *******************************************************************************************/
#include "processor\controlUnit.c"
#include "processor\processor.h"
#include "iounits\inputUnit.c"
#include "iounits\outputUnit.c"

int main(int argc, char** argv)
{
    outputString("Welcome in SIMDSysSim!\n");
    //outputString("Input subprocessor count: ");
    //subprocCount = inputInteger();
    //outputString("Starting a program...\n");
    for(subprocCount = 1; subprocCount < 37; subprocCount = subprocCount + 5)
    {
        startProgram();
    }
    return 1;
}