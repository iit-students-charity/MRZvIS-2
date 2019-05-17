#ifndef SIMD_HEADER_H
#define SIMD_HEADER_H

#include <stdio.h> //will be removed soon

#define UNARY_OPERATION_NAME enum unaryOperationName
UNARY_OPERATION_NAME
{
    ABSOLUTE, WAVE_UNAR_AND, WAVE_UNAR_OR
};
#define BINARY_OPERATION_NAME enum binaryOperationName
BINARY_OPERATION_NAME
{
    SUBSTRACT, MULTIPLICATION, IS_LESS, WAVE_BIN_AND, WAVE_IMPLICATION
};
#define MATR_NAME enum matrixName
MATR_NAME
{
    A, B, C, D, E, F
};

#endif // SIMD_HEADER_H