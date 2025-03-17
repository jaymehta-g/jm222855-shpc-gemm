#include "assignment3.h"

#define MR 4
#define NR 4

// multiply k by MR on NR by k
// expects column-major A and B
static void mkernel(double *A, double* B, double* C, int k) {
    int csA, rsB = k;
    int rsA = MR;
    int csB = NR;
    for (int i = 0; i < MR; i++)
    {
        for (int j = 0; j < NR; j++)
        {
            double dot = 0;
            for (int p = 0; p < k; p++)
            {
                mk
            }
            
        }
        
    }
    
}

void shpc_dgemm( int m, int n, int k,                                            
                    double *A, int rsA, int csA,                                
                    double *B, int rsB, int csB,                                
                    double *C, int rsC, int csC )
{

    // Your code goes here. 

}   
