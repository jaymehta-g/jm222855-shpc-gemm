#include "assignment3.h"
#include<immintrin.h>

#define MR 8
#define NR 6

#define RC(MAT, ROW, COL) MAT[ROW * rs##MAT + COL * cs##MAT]

// multiply k by MR on NR by k
// expects column-major A and row-major B
void mkernel(double *A, double* B, double* C, int k) {
    int rsA, rsB = 1;
    int csA = MR;
    int csB = k;
    int rsC = 1;
    int csC = MR;
    for (int i = 0; i < MR; i++)
    {
        for (int j = 0; j < NR; j++)
        {
            double dot = 0;
            for (int p = 0; p < k; p++)
            {
                dot += RC(A, i, p) * RC(B, p, j);
            }
            RC(C, i, j) += dot;
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
