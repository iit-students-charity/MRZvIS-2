#include "processor\controlUnit.c"
#include "processor\processor.h"
#include "iounits\inputUnit.c"
#include "iounits\outputUnit.c"

int main(int argc, char** argv)
{
    outputString("Welcome in SIMDSysSim!\n");
    outputString("Input subprocessor count: ");
    subprocCount = inputInteger();
    outputString("Starting a program...\n");

    startProgram();
    return 1;
}