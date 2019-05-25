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

void iterate3Bin_SMxSM(operation, SM1, SM2, x, y, z, targetTDM)
const BINARY_OPERATION_NAME operation;
const short*** SM1;
const short*** SM2;
const short x;
const short y;
const short z;
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
                callBinReg(operation, &(*SM1)[i][k], &(*SM2)[k][j], &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate3Bin_UMxD(operation, UM, D, x, y, z, targetTDM)
const BINARY_OPERATION_NAME operation;
const short** UM;
const short D;
const short x;
const short y;
const short z;
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
                callBinReg(operation, &(*UM)[k], &D, &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate3Bin_TDMxTDM(operation, TDM1, TDM2, x, y, z, targetTDM)
const BINARY_OPERATION_NAME operation;
const short**** TDM1;
const short**** TDM2;
const short x;
const short y;
const short z;
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
                callBinReg(operation, &(*TDM1)[i][j][k], &(*TDM2)[i][j][k], &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate3Bin_TDMxUM(operation, TDM, UM, x, y, z, targetTDM)
const BINARY_OPERATION_NAME operation;
const short**** TDM;
const short** UM;
const short x;
const short y;
const short z;
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
                callBinReg(operation, &(*TDM)[i][j][k], &(*UM)[k], &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}

void iterate3Bin_TDMxD(operation, TDM, D, x, y, z, targetTDM)
const BINARY_OPERATION_NAME operation;
const short**** TDM;
const short D;
const short x;
const short y;
const short z;
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
                callBinReg(operation, &(*TDM)[i][j][k], &D, &(*targetTDM)[i][j][k]);
                currentSubproc = switchSubproc(&currentSubproc);
            }
        }
    }
}