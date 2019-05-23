#include "subprocessor\register.c"

void iterate3Bin_SMxSM(operation, SM1, SM2, x, y, z, targetTDM)
const BINARY_OPERATION_NAME operation;
const short **SM1;
const short **SM2;
const short x;
const short y;
const short z;
const short ***targetTDM;
{
    int i;
    int j;
    int k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            for(k = 0; k < z; k++)
            {
                callBinReg(operation, &SM1[i][k], &SM2[k][j], &targetTDM[i][j][k]);
            }
        }
    }
}