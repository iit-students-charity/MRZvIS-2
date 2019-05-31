/*******************************************************************************************
 *
 * Лабораторная работа N2 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 * 
 * Элемент модели ОКМД, описывающий обработку входных матриц с передачей подпроцессорам
 * адресов отдельных элементов матриц.
 *
 * версия 1.0
 *
 *******************************************************************************************/
#include "subprocessor\register.c"
#include "processor.h"

int switchSubproc(current)
const int* current;
{
    if(*current < subprocCount)
    {
        return* current + 1;
    }
    else
    {
        return 1;
    }
}

void iterate_W_SMxSM_TDM(operation, SM1, SM2, x, y, z, targetTDM)
const OPERATION_NAME operation;
const short*** SM1;
const short*** SM2;
const int x;
const int y;
const int z;
const short**** targetTDM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                callReg(operation, &(*SM1)[i][k], &(*SM2)[k][j], &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate_WI_SMxSM_TDM(operation, SM1, SM2, x, y, z, targetTDM)
const OPERATION_NAME operation;
const short*** SM1;
const short*** SM2;
const int x;
const int y;
const int z;
const short**** targetTDM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                callReg(operation, &(*SM1)[k][j], &(*SM2)[i][k], &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate_UMxD_TDM(operation, UM, D, x, y, z, targetTDM)
const OPERATION_NAME operation;
const short** UM;
const short D;
const int x;
const int y;
const int z;
const short**** targetTDM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                callReg(operation, &(*UM)[k], &D, &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate_DxUM_TDM(operation, D, UM, x, y, z, targetTDM)
const OPERATION_NAME operation;
const short D;
const short** UM;
const int x;
const int y;
const int z;
const short**** targetTDM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                callReg(operation, &D, &(*UM)[k], &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate_TDMxTDM_TDM(operation, TDM1, TDM2, x, y, z, targetTDM)
const OPERATION_NAME operation;
const short**** TDM1;
const short**** TDM2;
const int x;
const int y;
const int z;
const short**** targetTDM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                callReg(operation, &(*TDM1)[i][j][k], &(*TDM2)[i][j][k], &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate_TDMxUM_TDM(operation, TDM, UM, x, y, z, targetTDM)
const OPERATION_NAME operation;
const short**** TDM;
const short** UM;
const int x;
const int y;
const int z;
const short**** targetTDM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                callReg(operation, &(*TDM)[i][j][k], &(*UM)[k], &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate_TDMxD_TDM(operation, TDM, D, x, y, z, targetTDM)
const OPERATION_NAME operation;
const short**** TDM;
const short D;
const int x;
const int y;
const int z;
const short**** targetTDM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                callReg(operation, &(*TDM)[i][j][k], &D, &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate_IUNAR_TDM_SM(operation, TDM, digit, x, y, targetSM)
const IUNAR_OPERATION_NAME operation;
const short**** TDM;
const int digit;
const int x;
const int y;
const short*** targetSM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            callUnarReg(operation, &(*TDM)[i][j], &digit, &(*targetSM)[i][j]);
            currentSubproc = switchSubproc(&currentSubproc);
        }
    }
}

void iterate_SMxD_SM(operation, SM, D, x, y, targetSM)
const IUNAR_OPERATION_NAME operation;
const short*** SM;
const short D;
const int x;
const int y;
const short*** targetSM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            callReg(operation, &(*SM)[i][j], &D, &(*targetSM)[i][j]);
            currentSubproc = switchSubproc(&currentSubproc);
        }
    }
}

void iterate_DxSM_SM(operation, D, SM, x, y, targetSM)
const IUNAR_OPERATION_NAME operation;
const short D;
const short*** SM;
const int x;
const int y;
const short*** targetSM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            callReg(operation, &D, &(*SM)[i][j], &(*targetSM)[i][j]);
            currentSubproc = switchSubproc(&currentSubproc);
        }
    }
}

void iterate_SMxSM_SM(operation, SM1, SM2, x, y, targetSM)
const IUNAR_OPERATION_NAME operation;
const short*** SM1;
const short*** SM2;
const int x;
const int y;
const short*** targetSM;
{
    int currentSubproc = 1;

    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            callReg(operation, &(*SM1)[i][j], &(*SM2)[i][j], &(*targetSM)[i][j]);
            currentSubproc = switchSubproc(&currentSubproc);
        }
    }
}