/*******************************************************************************************
 *
 * Лабораторная работа N2 по дисциплине "Модели Решения Задач в Интеллектуальных Системах"
 * выполнено студентом БГУИР группы 721703
 * Клюевым Александром Алексеевичем
 * 
 * Управляющий элемент в ОКМД. Тут описан набор команд програмы, в том числе запросы на
 * обработку процессорами каких-либо матриц и областей памяти. Не хранит в себе сами
 * данные матриц, а только их адреса и их ячеек.
 *
 * версия 1.0
 *
 *******************************************************************************************/
#include "processor.h"
#include "procBus.c"
#include "..\iounits\inputUnit.c"
#include "..\iounits\outputUnit.c"

void generateInitialMatrixes(p, q, m)
const int p;
const int q;
const int m;
{
    generateMatrix(&matrixA, p, m);
    generateMatrix(&matrixB, m, q);
    generateMatrix(&matrixE, 1, m);
    generateMatrix(&matrixG, p, q);
}

void calculateMatrixD(p, q, m)
const int p;
const int q;
const int m;
{
    initTriDimMatrix(&matrixD, p, q, m);

    iterate_W_SMxSM_TDM(WAVE_BIN_AND, &matrixA, &matrixB, p, q, m, &matrixD, 2);
}

void calculateMatrixF(p, q, m)
const int p;
const int q;
const int m;
{
    const int SUBEXPRESSION_LEVELS_COUNT = 3;

    initTriDimMatrix(&matrixF, p, q, m);
    initFourDimMatrix(&TDBuffer, SUBEXPRESSION_LEVELS_COUNT, p, q, m);

//                      |OPERATION        |OPERAND1           |OPERAND2     |X |Y |Z |TARGET       |r |
    iterate_W_SMxSM_TDM( WAVE_IMPLICATION, &matrixA,           &matrixB,     p, q, m, &TDBuffer[1], 2);
    iterate_UMxD_TDM(    MULTIPLICATION,   &matrixE[0],        2,            p, q, m, &TDBuffer[2], 1);
    iterate_UMxD_TDM(    SUBSTRACT,        &TDBuffer[2][0][0], 1,            p, q, m, &TDBuffer[2], 1);
    iterate_TDMxTDM_TDM( MULTIPLICATION,   &TDBuffer[1],       &TDBuffer[2], p, q, m, &TDBuffer[1], 3);
    iterate_TDMxUM_TDM(  MULTIPLICATION,   &TDBuffer[1],       &matrixE[0],  p, q, m, &TDBuffer[1], 4);
    eqTriDimMatr(&TDBuffer[0], &TDBuffer[1], p, q, m);
    iterate_WI_SMxSM_TDM(WAVE_IMPLICATION, &matrixB,           &matrixA,     p, q, m, &TDBuffer[1], 2);
    iterate_W_SMxSM_TDM( WAVE_IMPLICATION, &matrixA,           &matrixB,     p, q, m, &TDBuffer[2], 2);
    iterate_TDMxD_TDM(   MULTIPLICATION,   &TDBuffer[2],       4,            p, q, m, &TDBuffer[2], 2);
    iterate_TDMxD_TDM(   SUBSTRACT,        &TDBuffer[2],       2,            p, q, m, &TDBuffer[2], 2);
    iterate_TDMxUM_TDM(  MULTIPLICATION,   &TDBuffer[2],       &matrixE[0],  p, q, m, &TDBuffer[2], 3);
    iterate_TDMxD_TDM(   ADDITION,         &TDBuffer[2],       1,            p, q, m, &TDBuffer[2], 3);
    iterate_TDMxTDM_TDM( MULTIPLICATION,   &TDBuffer[1],       &TDBuffer[2], p, q, m, &TDBuffer[1], 5);
    iterate_DxUM_TDM(    SUBSTRACT,        1,                  &matrixE[0],  p, q, m, &TDBuffer[2], 1);
    iterate_TDMxTDM_TDM( MULTIPLICATION,   &TDBuffer[1],       &TDBuffer[2], p, q, m, &TDBuffer[1], 6);
    iterate_TDMxTDM_TDM( ADDITION,         &TDBuffer[0],       &TDBuffer[1], p, q, m, &TDBuffer[0], 10);

    eqTriDimMatr(&matrixF, &TDBuffer[0], p, q, m);
    freeFourDimMatrix(&TDBuffer, SUBEXPRESSION_LEVELS_COUNT, p, q, m);
}

void calculateMatrixC(p, q, m)
const int p;
const int q;
const int m;
{
    const int SUBEXPRESSION_LEVELS_COUNT = 4;

    initSquareMatrix(&matrixC, p, q);
    initTriDimMatrix(&SBuffer, SUBEXPRESSION_LEVELS_COUNT, p, q);

//                      |OPERATION      |OPERAND1    |OPERAND2    |X |Y |TARGET      |r          |
    iterate_IUNAR_TDM_SM(WAVE_UNAR_AND,  &matrixF,    m,           p, q, &SBuffer[1], 10 * m);
    iterate_SMxD_SM(     MULTIPLICATION, &matrixG,    3,           p, q, &SBuffer[2], 1);
    iterate_SMxD_SM(     SUBSTRACT,      &SBuffer[2], 2,           p, q, &SBuffer[2], 1);
    iterate_SMxSM_SM(    MULTIPLICATION, &SBuffer[1], &SBuffer[2], p, q, &SBuffer[1], 10 * m + 1);
    iterate_SMxSM_SM(    MULTIPLICATION, &SBuffer[1], &matrixG,    p, q, &SBuffer[1], 10 * m + 2);
    eqSqMatr(&SBuffer[0], &SBuffer[1], p, q);
    iterate_IUNAR_TDM_SM(WAVE_UNAR_OR,   &matrixD,    m,           p, q, &SBuffer[1], 2  * m);
    iterate_IUNAR_TDM_SM(WAVE_UNAR_AND,  &matrixF,    m,           p, q, &SBuffer[2], 10 * m);
    iterate_IUNAR_TDM_SM(WAVE_UNAR_OR,   &matrixD,    m,           p, q, &SBuffer[3], 2  * m);
    iterate_SMxSM_SM(    MULTIPLICATION, &SBuffer[2], &SBuffer[3], p, q, &SBuffer[2], 12 * m);
    iterate_SMxD_SM(     MULTIPLICATION, &SBuffer[2], 4,           p, q, &SBuffer[2], 12 * m);
    iterate_IUNAR_TDM_SM(WAVE_UNAR_OR,   &matrixD,    m,           p, q, &SBuffer[3], 2  * m);
    iterate_SMxD_SM(     MULTIPLICATION, &SBuffer[3], 3,           p, q, &SBuffer[3], 2  * m);
    iterate_SMxSM_SM(    SUBSTRACT,      &SBuffer[2], &SBuffer[3], p, q, &SBuffer[2], 14 * m);
    iterate_SMxSM_SM(    MULTIPLICATION, &SBuffer[2], &matrixG,    p, q, &SBuffer[2], 14 * m + 1);
    iterate_SMxSM_SM(    ADDITION,       &SBuffer[1], &SBuffer[2], p, q, &SBuffer[1], 16 * m + 1);
    iterate_DxSM_SM(     SUBSTRACT,      1,           &matrixG,    p, q, &SBuffer[2], 1);
    iterate_SMxSM_SM(    MULTIPLICATION, &SBuffer[1], &SBuffer[2], p, q, &SBuffer[1], 16 * m + 2);
    iterate_SMxSM_SM(    ADDITION,       &SBuffer[0], &SBuffer[1], p, q, &SBuffer[0], 26 * m + 4);

    eqSqMatr(&matrixC, &SBuffer[0], p, q);
    freeTriDimMatrix(&SBuffer, SUBEXPRESSION_LEVELS_COUNT, p, q);
}

void startProgram()
{
    /*outputString("Input addition calculation time: ");
    additionTime = inputInteger();
    outputString("Input substraction calculation time: ");
    substractionTime = inputInteger();
    outputString("Input multiplication calculation time: ");
    multiplicationTime = inputInteger();
    outputString("Input comparation calculation time: ");
    comparationTime = inputInteger();
    outputString("Input p: ");
    p = inputInteger();
    outputString("Input q: ");
    q = inputInteger();
    outputString("Input m: ");
    m = inputInteger();*/
    additionTime = substractionTime = multiplicationTime = comparationTime = 1;
    p = q = m = 1;
    //outputString("Generating initial matrixes...\n");

    generateInitialMatrixes(p, q, m);

    //outputString("Initial matrixes successfuly generated!\n");
    /*outputString("Would you like to print them?(1 - yes, 0 - no)\n");
    int i = inputInteger();
    if(i == 1)
    {
        outputSquareMatrix("A", &matrixA, p, m);
        outputSquareMatrix("B", &matrixB, m, q);
        outputSquareMatrix("E", &matrixE, 1, m);
        outputSquareMatrix("G", &matrixG, p, q);
    }*/
    //outputString("Calculating target matrixes...\n");
    //outputString("Calculating D matrix...\n");

    calculateMatrixD(p, q, m);

    //outputString("D matrix calculated!\n");
    /*outputString("Would you like to print it?(1 - yes, 0 - no)\n");
    i = inputInteger();
    if(i == 1)
    {
        outputTriDimMatrix("D", &matrixD, p, q, m);
    }*/
    //outputString("Calculating F matrix...\n");

    calculateMatrixF(p, q, m);
    freeSquareMatrix(&matrixA, p, m);
    freeSquareMatrix(&matrixB, m, q);
    freeSquareMatrix(&matrixE, 1, m);

    //outputString("F matrix calculated!\n");
    /*outputString("Would you like to print it?(1 - yes, 0 - no)\n");
    i = inputInteger();
    if(i == 1)
    {
        outputTriDimMatrix("F", &matrixF, p, q, m);
    }*/
    //outputString("Calculating C matrix...\n");

    calculateMatrixC(p, q, m);
    freeSquareMatrix(&matrixG, p, q);
    freeTriDimMatrix(&matrixF, p, q, m);
    freeTriDimMatrix(&matrixD, p, q, m);

    //outputString("C matrix calculated!\n");
    /*outputString("Would you like to print it?(1 - yes, 0 - no)\n");
    i = inputInteger();
    if(i == 1)
    {
        outputSquareMatrix("C", &matrixC, p, q);
    }*/
    //outputString("Target matrixes are successfuly calculated!\n");

    Lavg = ceil((float)Lavg / (p * q * (26 * m + 4)));

    printf("\nModel metrics:\n");
    printf("Rang_____________________r  = %d\n", p * q * (26 * m + 4));
    printf("Subprocessor count_______n  = %d\n", subprocCount);
    printf("Linear run time__________T1 = %d\n", runTime);
    printf("Paralel run time_________Tn = %d\n", subprocessorRunTime);
    printf("Acceleration coefficient_Ky = %f\n", runTime / (float)subprocessorRunTime);
    printf("Effectiveness____________e  = %f\n", runTime / (float)(subprocessorRunTime * subprocCount));
    printf("Summar operation length__Lsum = %d\n", Lsum);
    printf("Average operation length_Lavg = %d\n", Lavg);
    printf("Divergence coefficient___D = %d,%6.f\n", Lsum / Lavg, ((Lsum / (float)Lavg) - (int)(Lsum / Lavg)) * 1000000);
    //printf("\nWould you like to exit the program?(input anything to agree)");
    
    freeSquareMatrix(&matrixC, p, q);
    runTime = subprocessorRunTime = stageTime = Lsum = Lavg = 0;
    //inputInteger();
}