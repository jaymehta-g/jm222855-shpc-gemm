#include "assignment3.h"
#include <immintrin.h>

#define min(a,b) ((a) < (b) ? (a) : (b))

#define MR 8
#define NR 6

#define MC 608
#define NC 1296
#define KC 402

#define RC(MAT, ROW, COL) MAT[ROW * rs##MAT + COL * cs##MAT]

#define UKERN_LOOP(COL) \
        a_top = _mm256_loadu_pd(&RC(A, 0, p)); \
        a_bot = _mm256_loadu_pd(&RC(A, 4, p)); \
        b_broadcast = _mm256_broadcast_sd(&RC(B, p, COL)); \
        c_0_ ## COL = _mm256_fmadd_pd(a_top, b_broadcast, c_0_ ## COL); \
        c_1_ ## COL = _mm256_fmadd_pd(a_bot, b_broadcast, c_1_ ## COL);

// multiply k by MR on NR by k
// expects column-major A and row-major B
// excepts column major C
// A is MR x k, B is k x NR
void mkernel(double *A, double* B, double* C, int rsC, int csC, int k) {
    const int rsA = 1, csB = 1;
    const csA = MR;
    const rsB = NR;
    __m256d c_0_0 = _mm256_loadu_pd(&RC(C, 0, 0));
    __m256d c_0_1 = _mm256_loadu_pd(&RC(C, 0, 1));
    __m256d c_0_2 = _mm256_loadu_pd(&RC(C, 0, 2));
    __m256d c_0_3 = _mm256_loadu_pd(&RC(C, 0, 3));
    __m256d c_0_4 = _mm256_loadu_pd(&RC(C, 0, 4));
    __m256d c_0_5 = _mm256_loadu_pd(&RC(C, 0, 5));
    __m256d c_1_0 = _mm256_loadu_pd(&RC(C, 4, 0));
    __m256d c_1_1 = _mm256_loadu_pd(&RC(C, 4, 1));
    __m256d c_1_2 = _mm256_loadu_pd(&RC(C, 4, 2));
    __m256d c_1_3 = _mm256_loadu_pd(&RC(C, 4, 3));
    __m256d c_1_4 = _mm256_loadu_pd(&RC(C, 4, 4));
    __m256d c_1_5 = _mm256_loadu_pd(&RC(C, 4, 5));

    for (int p = 0; p < k; p++)
    {
        __m256d b_broadcast;
        __m256d a_top;
        __m256d a_bot;

        UKERN_LOOP(0);
        UKERN_LOOP(1);
        UKERN_LOOP(2);
        UKERN_LOOP(3);
        UKERN_LOOP(4);
        UKERN_LOOP(5);
    }

    _mm256_storeu_pd(&RC(C,0,0), c_0_0);
    _mm256_storeu_pd(&RC(C,0,1), c_0_1);
    _mm256_storeu_pd(&RC(C,0,2), c_0_2);
    _mm256_storeu_pd(&RC(C,0,3), c_0_3);
    _mm256_storeu_pd(&RC(C,0,4), c_0_4);
    _mm256_storeu_pd(&RC(C,0,5), c_0_5);
    _mm256_storeu_pd(&RC(C,4,0), c_1_0);
    _mm256_storeu_pd(&RC(C,4,1), c_1_1);
    _mm256_storeu_pd(&RC(C,4,2), c_1_2);
    _mm256_storeu_pd(&RC(C,4,3), c_1_3);
    _mm256_storeu_pd(&RC(C,4,4), c_1_4);
    _mm256_storeu_pd(&RC(C,4,5), c_1_5);
}

void shpc_dgemm( int m, int n, int k,                                            
                    double *A, int rsA, int csA,                                
                    double *B, int rsB, int csB,                                
                    double *C, int rsC, int csC )
{

    // Your code goes here. 
    
}   
